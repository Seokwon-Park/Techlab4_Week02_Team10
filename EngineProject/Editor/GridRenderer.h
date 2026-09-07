#pragma once

#include <d3d11.h>
#include "Renderer.h"

class FGridRenderer
{
public:
	~FGridRenderer();

	bool Init(FRenderer* InRenderer);
	void OnRender(const FMatrix& World, const FMatrix& ViewProj);
	
private:
	FRenderer* Renderer;

	TSharedPtr<FVertexBuffer> VB;
	TSharedPtr<FIndexBuffer> IB;
};