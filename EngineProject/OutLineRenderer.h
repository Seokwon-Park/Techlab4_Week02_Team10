#pragma once

#include "Renderer.h"
#include "Outline.h"

class FOutlineRenderer
{
public:

	void Init(FRenderer* InRenderer);
	void SetMesh(FMesh* InMesh);
	void OnRender(const FOutline& InOutline, const FMatrix& ViewProj);
	
private:
	FRenderer* Renderer;

	FShader* Shader;
	FMesh* Mesh;

	Microsoft::WRL::ComPtr<ID3D11RasterizerState> RasterizerState;
};