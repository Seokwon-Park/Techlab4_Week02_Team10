#pragma once

#include <d3d11.h>
#include "Renderer.h"

enum class EGizmoMode
{
	Location,
	Rotation,
	Scale,
};

struct FGizmoData
{
	FMatrix World;
	FMatrix ViewProj;
	FVector4 Color;
};

class FGizmoRenderer
{
public:
	FGizmoRenderer();
	~FGizmoRenderer() = default;

	bool Init(FRenderer* InRenderer);
	void OnRender(const FMatrix& ViewProj);

private:
	FRenderer* Renderer;

	FTransform Transform;
	FMatrix World;

	TArray<FGizmoData> AxisDataArray;

	TSharedPtr<FShader> Shader;
	TSharedPtr<FMesh> LocationMesh;
	TSharedPtr<FMesh> RotationMesh;
	TSharedPtr<FMesh> ScaleMesh;
	TSharedPtr<FMesh> SphereMesh;
	TSharedPtr<FConstantBuffer> CB;

	EGizmoMode Mode = EGizmoMode::Scale;
};