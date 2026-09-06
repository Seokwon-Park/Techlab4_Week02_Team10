#pragma once
#pragma comment(lib, "user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl/client.h>

#include "RenderPacket.h"

struct FVertexSimple
{	// test
	float x, y, z;
	float r, g, b, a;
};

class FRenderer
{
public:
	void BeginFrame();
	void EndFrame();

	void Create(HWND hWindow);

	void CreateDeviceAndSwapChain(HWND hWindow);
	void CreateFrameBuffer();
	void CreateRasterizerState();
	void CreateDepthStencilBufferAndState();

	inline ID3D11Device* GetDevice() const { return Device.Get(); }
	ID3D11DeviceContext* GetDeviceContext();

	FShader* CreateShader(const wchar_t* FileName, D3D11_INPUT_ELEMENT_DESC* InLayoutDesc, size_t InLayoutSize);
	FMesh* CreateMesh(const void* Vertices, uint32 VertexCount, uint32 Stride,
		const uint32* Indices = nullptr, uint32 IndexCount = 0);

	ID3D11Buffer* CreateVertexBuffer(const void* InVertices, UINT InByteWidth);
	ID3D11Buffer* CreateIndexBuffer(const uint32* InIndices, UINT InByteWidth);

	void BindShader(FShader* InShader);
	void BindBuffer(FMesh* InMesh);
	void Draw(int IndexCount);

	void Prepare();
	void RenderPrimitive(ID3D11Buffer* pVertexBuffer, UINT InNumVertices, ID3D11Buffer* pIndexBuffer, UINT InNumIndices, UINT InStride);

	void RenderAll(TQueue<FRenderPacket>& InQueue);
	void Shutdown();

private:

	Microsoft::WRL::ComPtr<ID3D11Device> Device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> DeviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> SwapChain;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> FrameBuffer;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> FrameBufferRTV;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> DepthStencilBuffer;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> DepthStencilState;

	Microsoft::WRL::ComPtr<ID3D11RasterizerState> RasterizerState;

	Microsoft::WRL::ComPtr <ID3D11Buffer> ConstantBuffer;
	D3D11_VIEWPORT ViewportInfo;

	FLOAT ClearColor[4] = {0.3f, 0.3f, 0.3f, 1.0f };
};