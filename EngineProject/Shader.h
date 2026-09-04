#pragma once
#include <wrl/client.h>
#include "Types.h"

class ID3D11VertexShader;
class ID3D11PixelShader;
class ID3D11InputLayout;
class FRenderer;

class FShader
{
public:
	void Create(FRenderer* InRenderer);
	void Init(const wchar_t* InFile, uint32 InStride);

private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> VertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> PixelShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> InputLayout;

	uint32 Stride;
	const wchar_t* File;
};
