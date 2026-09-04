#include "Shader.h"
#include "Renderer.h"

void FShader::Create(FRenderer* InRenderer)
{
	// 셰이더 컴파일 함수 호출
}

void FShader::Init(const wchar_t* InFile, uint32 InStride)
{
	File = InFile;
	Stride = InStride;
}
