#pragma once

#include <d3d11.h>
#include "Renderer.h"

class FGridRenderer
{
public:
	~FGridRenderer();

	inline void SetRenderer(FRenderer* InRenderer) { Renderer = InRenderer; }

	bool Init();
	void OnRender();
	
private:
	FRenderer* Renderer;

	ID3D11Buffer* VB;
	ID3D11Buffer* IB;
};