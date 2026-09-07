#pragma once

#include <d3d11.h>
#include "Renderer.h"

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

	TSharedPtr<FMesh> ArrowMesh;
	TSharedPtr<FMesh> SphereMesh;
};