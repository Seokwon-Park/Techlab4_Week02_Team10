#include "EnginePCH.h"
#include "Gizmo.h"
#include "Component/CameraComponent.h"

static const FVector AxisDirs[3] = {
	FVector(1, 0, 0),
	FVector(0, 1, 0),
	FVector(0, 0, 1),
};

static const float AxisLength = 1.5f;
static const float HitPixels = 12.0f;

void FGizmo::Update(const FRay& MouseRay, const FVector2& MousePos, const FMatrix& ViewProj, int ScreenW, int ScreenH, bool bMouseDown, UCameraComponent* CameraComponent)
{
	FGizmo::CameraComponent = CameraComponent;

	if (!Target)
	{
		HoveredAxis = -1;
		DraggingAxis = -1;
		return;
	}

	if (DraggingAxis >= 0)
	{
		if (bMouseDown)
			UpdateDrag(MouseRay);
		else
			EndDrag();
		return;
	}

	HoveredAxis = PickAxis(MousePos, ViewProj, ScreenW, ScreenH);

	if (bMouseDown && HoveredAxis >= 0)
		BeginDrag(HoveredAxis, MouseRay);

	
}

int FGizmo::PickAxis(const FVector2& MousePos, const FMatrix& ViewProj, int ScreenW, int ScreenH)
{
	if (Mode == EGizmoMode::Rotation)
		return PickRotationAxis(MousePos, ViewProj, ScreenW, ScreenH);

	return PickLinearAxis(MousePos, ViewProj, ScreenW, ScreenH);
}

int FGizmo::PickLinearAxis(const FVector2& MousePos, const FMatrix& ViewProj, int ScreenW, int ScreenH)
{
	FVector origin = GetRenderLocation();

	int best = -1;
	float bestDist = HitPixels;

	for (int i = 0; i < 3; ++i)
	{
		FVector2 start = WorldToScreen(origin, ViewProj, ScreenW, ScreenH);
		FVector2 end = WorldToScreen(origin + GetAxisDirection(i) * AxisLength, ViewProj, ScreenW, ScreenH);

		float dist = DistanceToSegment(MousePos, start, end);
		if (dist < bestDist)
		{
			bestDist = dist;
			best = i;
		}
	}
	return best;
}

int FGizmo::PickRotationAxis(const FVector2& MousePos, const FMatrix& ViewProj, int ScreenW, int ScreenH)
{
	const FVector Origin = GetLocation();
	const int Segments = 32;

	int best = -1;
	float bestDist = HitPixels;

	for (int axis = 0; axis < 3; ++axis)
	{
		FVector u = AxisDirs[(axis + 1) % 3];
		FVector v = AxisDirs[(axis + 2) % 3];

		FVector2 prev;
		bool bHasPrev = false;

		for (int s = 0; s <= Segments; ++s)
		{
			float theta = (float)s / Segments * 2.0f * PI;
			FVector worldPos = Origin
				+ u * (RingRadius * cosf(theta))
				+ v * (RingRadius * sinf(theta));

			FVector2 screenPos = WorldToScreen(worldPos, ViewProj, ScreenW, ScreenH);

			if (bHasPrev)
			{
				float dist = DistanceToSegment(MousePos, prev, screenPos);
				if (dist < bestDist)
				{
					bestDist = dist;
					best = axis;
				}
			}

			prev = screenPos;
			bHasPrev = true;
		}
	}

	return best;
}

void FGizmo::BeginDrag(int Axis, const FRay& MouseRay)
{
	DraggingAxis = Axis;
	DragStartLocation = GetLocation();
	DragStartRotation = GetRotation();
	DragStartScale = GetScale();

	DragAxisDirection = GetAxisDirection(Axis);   // ← 여기 추가
	FVector axis = DragAxisDirection;              // ← 아래에서 이걸 씀

	if (Mode == EGizmoMode::Rotation)
	{
		DragPlaneNormal = axis;   // 링 평면
	}
	else
	{
		FVector toCamera = -MouseRay.Direction;
		FVector ortho = axis.Cross(toCamera);
		DragPlaneNormal = ortho.Cross(axis).Normalize();
	}

	float t;
	if (RayIntersectsPlane(MouseRay, DragStartLocation, DragPlaneNormal, t))
		DragStartPoint = MouseRay.Origin + MouseRay.Direction * t;
	else
		DragStartPoint = DragStartLocation;

	if (Mode == EGizmoMode::Rotation)
		DragStartAngle = ComputeAngleOnPlane(DragStartPoint, Axis);
}

void FGizmo::UpdateDrag(const FRay& MouseRay)
{
	float t;
	if (!RayIntersectsPlane(MouseRay, DragStartLocation, DragPlaneNormal, t))
		return;

	FVector current = MouseRay.Origin + MouseRay.Direction * t;
	if (Mode == EGizmoMode::Rotation)
	{
		float currentAngle = ComputeAngleOnPlane(current, DraggingAxis);
		float deltaAngle = currentAngle - DragStartAngle;   

		FQuat delta = FQuat::MakeFromAxisAngle(DragAxisDirection, deltaAngle);  
		FQuat start = DragStartRotation.Quaternion();

		FQuat result = delta * start;   

		Target->GetTransform()->Rotation = result.ToFRotator();
		return;
	}

	FVector delta = current - DragStartPoint;
	float amount = delta.Dot(DragAxisDirection);

	if (Mode == EGizmoMode::Location)
		Target->GetTransform()->Location = DragStartLocation + DragAxisDirection * amount;
	else   // Scale
	{
		float factor = 1.0f + amount;
		if (factor < 0.01f) factor = 0.01f;

		FVector NewScale = DragStartScale;
		if (DraggingAxis == 0)      NewScale.X *= factor;
		else if (DraggingAxis == 1) NewScale.Y *= factor;
		else                        NewScale.Z *= factor;

		Target->GetTransform()->Rotation;  
		Target->GetTransform()->Scale = NewScale;
	}
}

void FGizmo::EndDrag()
{
	DraggingAxis = -1;
}

float FGizmo::ComputeAngleOnPlane(const FVector& Point, int Axis) const
{
	FVector u = AxisDirs[(Axis + 1) % 3];
	FVector v = AxisDirs[(Axis + 2) % 3];

	FVector local = Point - GetLocation();
	return atan2f(local.Dot(v), local.Dot(u));
}

FVector FGizmo::GetAxisDirection(int Axis) const
{
	bool bUseLocal = (Space == EGizmoSpace::Local) || (Mode == EGizmoMode::Scale);

	if (bUseLocal && Target)
	{
		FMatrix rot = Target->GetTransform()->Rotation.Quaternion().ToFMatrix();
		FVector4 v = rot.TransformVector(AxisDirs[Axis]);
		return FVector(v.X, v.Y, v.Z).Normalize();
	}
	return AxisDirs[Axis];
}

FVector FGizmo::GetRenderLocation() const
{
	if (!Target) return FVector(0, 0, 0);

	if (CameraComponent->bIsOrthogonal) return GetLocation();

	return (Target->GetTransform()->Location - CameraComponent->GetTransform()->Location).Normalize() * 10.0f + CameraComponent->GetTransform()->Location;

	// return Target ? Target->GetTransform()->Location: FVector(0, 0, 0); 
}