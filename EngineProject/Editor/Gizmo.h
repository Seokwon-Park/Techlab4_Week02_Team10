#pragma once

#include "Ray.h"
#include "Transform.h"
#include "Component/SceneComponent.h"

enum class EGizmoMode
{
	Location,
	Rotation,
	Scale,
};

class FGizmo   // 상태 + 로직
{
public:
	// Gizmo 대상 설정
	void SetTarget(USceneComponent* InTarget) { Target = InTarget; }
	USceneComponent* GetTarget() const { return Target; }

	// Gizmo 모드(이동, 회전, 크기)
	void SetMode(EGizmoMode InMode) { Mode = InMode; }
	EGizmoMode GetMode() const { return Mode; }

	void Update(const FRay& MouseRay, const FVector2& MousePos,
		const FMatrix& ViewProj, int ScreenW, int ScreenH,
		bool bMouseDown);

	bool IsUsing() const { return DraggingAxis >= 0; }
	int GetHoveredAxis() const { return HoveredAxis; }

	int PickAxis(const FVector2& MousePos, const FMatrix& ViewProj, int ScreenW, int ScreenH);

	void BeginDrag(int Axis, const FRay& MouseRay);
	void UpdateDrag(const FRay& MouseRay);
	void EndDrag();

	inline FVector GetLocation() const { return Target ? Target->GetTransform()->Location: FVector(0, 0, 0); }
	inline FVector GetScale() const { return Target ? Target->GetTransform()->Scale: FVector(0, 0, 0); }

private:
	EGizmoMode Mode = EGizmoMode::Location;
	FTransform Transform = FTransform();
	USceneComponent* Target = nullptr;

	int HoveredAxis = -1;
	int DraggingAxis = -1;

	FVector DragStartPoint;
	FVector DragStartLocation;
	FVector DragStartScale;
	FVector DragPlaneNormal;
};