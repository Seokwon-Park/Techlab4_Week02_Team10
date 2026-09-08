#pragma once

#include <d3d11.h>
#include <wrl.h>

using namespace Microsoft::WRL;

class FIndexBuffer
{
public:
	FIndexBuffer(ID3D11Device* Device, const uint32* Indices, uint32 IndexCount);
	~FIndexBuffer() = default;

	inline uint32 GetIndexCount() const { return IndexCount; }
	inline ID3D11Buffer* GetBuffer() const { return Buffer.Get(); }

private:
	uint32 IndexCount;
	ComPtr<ID3D11Buffer> Buffer;

};

class FVertexBuffer
{
public:
	FVertexBuffer(ID3D11Device* Device, const void* Vertices, uint32 TotalSize, uint32 InStride);
	~FVertexBuffer() = default;

	inline uint32 GetStride() const { return Stride; }
	inline ID3D11Buffer* GetBuffer() const { return Buffer.Get(); }

private:
	uint32 Stride;
	ComPtr<ID3D11Buffer> Buffer;

};