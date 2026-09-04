#include "EnginePCH.h"
#include "Shader.h"
#include "Renderer.h"

FShader* FShader::Create(FRenderer* InRenderer)
{
	D3D11_INPUT_ELEMENT_DESC layout[] =	// 셰이더 리플렉션 기능 추후 구현 필요
	{
		{"POSITION" , 0 , DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"SCALE", 0, DXGI_FORMAT_R32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	// 셰이더 컴파일 함수 호출
	InRenderer->CreateShader(this, layout, ARRAYSIZE(layout));

	return this;
}

void FShader::Init(const wchar_t* InFile, const char* InVsFunctionName, const char* InPsFunctionName, uint32 InStride)
{
	File = InFile;
	Stride = InStride;
	VertexFunctionName = InVsFunctionName;
	PixelFunctionName = InPsFunctionName;
}
