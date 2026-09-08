#include "EnginePCH.h"
#include "Gizmo.h"

static const FVector AxisDirs[3] = {
	FVector(1, 0, 0),
	FVector(0, 1, 0),
	FVector(0, 0, 1),
};

static const float AxisLength = 1.5f;
static const float HitPixels = 12.0f;

void FGizmo::Update(const FRay& MouseRay, const FVector2& MousePos, const FMatrix& ViewProj, int ScreenW, int ScreenH, bool bMouseDown)
{
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
	FVector origin = GetLocation();

	int best = -1;
	float bestDist = HitPixels;

	for (int i = 0; i < 3; ++i)
	{
		FVector2 start = WorldToScreen(origin, ViewProj, ScreenW, ScreenH);
		FVector2 end = WorldToScreen(origin + AxisDirs[i] * AxisLength, ViewProj, ScreenW, ScreenH);

		float dist = DistanceToSegment(MousePos, start, end);
		if (dist < bestDist)
		{
			bestDist = dist;
			best = i;
		}
	}
	return best;
}

void FGizmo::BeginDrag(int Axis, const FRay& MouseRay)
{
	DraggingAxis = Axis;
	DragStartLocation = GetLocation();
	DragStartScale = GetScale();

	// 축을 포함하면서 카메라를 최대한 향하는 평면 만들기
	FVector axis = AxisDirs[Axis];
	FVector toCamera = -MouseRay.Direction;
	FVector ortho = axis.Cross(toCamera);
	DragPlaneNormal = ortho.Cross(axis).Normalize();

	float t;
	if (RayIntersectsPlane(MouseRay, DragStartLocation, DragPlaneNormal, t))
		DragStartPoint = MouseRay.Origin + MouseRay.Direction * t;
	else
		DragStartPoint = DragStartLocation;
}

void FGizmo::UpdateDrag(const FRay& MouseRay)
{
	float t;
	if (!RayIntersectsPlane(MouseRay, DragStartLocation, DragPlaneNormal, t))
		return;

	FVector current = MouseRay.Origin + MouseRay.Direction * t;
	FVector delta = current - DragStartPoint;

	FVector axis = AxisDirs[DraggingAxis];
	float amount = delta.Dot(axis);   // 축 방향 성분만

	switch (Mode)
	{
	case EGizmoMode::Location:
		Target->GetTransform()->Location = FVector(DragStartLocation + axis * amount);
		break;

	case EGizmoMode::Scale:
		Target->GetTransform()->Scale = FVector(DragStartScale + axis * amount);
		break;

	case EGizmoMode::Rotation:
		// 각도 계산 필요 - 아래 설명
		break;
	}
}

void FGizmo::EndDrag()
{
	DraggingAxis = -1;
}
