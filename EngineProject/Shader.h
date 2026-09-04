#pragma once
#include <wrl/client.h>
#include "Types.h"

class ID3D11VertexShader;
class ID3D11PixelShader;
class ID3D11InputLayout;
class FRenderer;

class FShader
{
	// vs, ps 쌍으로 관리하도록 함
	// 추후 리팩토링
	friend FRenderer;
public:
	FShader* Create(FRenderer* InRenderer);
	void Init(const wchar_t* InFile, const char* InFunctionName, const char* InPsFunctionName, uint32 InStride);

private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> VertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> PixelShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> InputLayout;
	 
	uint32 Stride;
	const wchar_t* File;	// hlsl 파일 하나만
	const char* VertexFunctionName;
	const char* PixelFunctionName;
};
