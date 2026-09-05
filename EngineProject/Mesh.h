#pragma once

#pragma comment(lib, "user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl/client.h>

class FMesh
{
public:
	FMesh* Create(void* InVertices, uint32 InNumVertices, void* InIndices, uint32 InNumIndices, uint32 InStride);

	ID3D11Buffer* GetVertexBuffer();
	ID3D11Buffer* GetIndexBuffer();

	uint32 GetNumVertices(){ return NumVertices; }
	uint32 GetNumIndices() { return NumIndices; }
	uint32 GetStride() { return Stride; }
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> VertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> IndexBuffer;

	DXGI_FORMAT IndexFormat;

	uint32 Stride;

	uint32 NumVertices;
	uint32 NumIndices;
};