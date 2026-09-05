#pragma once
#pragma comment(lib, "user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl/client.h>

class FShader;

struct FVertexSimple
{	// test
	float x, y, z;
	float r, g, b, a;
};



class FRenderer
{
	// 마이어스 Singleton
private:
	FRenderer() = default;
public:
	FRenderer(const FRenderer& src) = delete;
	FRenderer& operator= (const FRenderer& src) = delete;
	static FRenderer& GetInstance();

	void Create(HWND hWindow);

	void CreateDeviceAndSwapChain(HWND hWindow);
	void CreateFrameBuffer();
	void CreateRasterizerState();
	void CreateDepthStencilBufferAndState();
	void SwapBuffer();

	void CreateShader(FShader* InShader, D3D11_INPUT_ELEMENT_DESC* InLayoutDesc, size_t InLayoutSize);

	ID3D11Buffer* CreateVertexBuffer(void* InVertices, UINT InByteWidth);
	ID3D11Buffer* CreateIndexBuffer(void* InIndices, UINT InByteWidth);

	void Prepare();
	void RenderPrimitive(ID3D11Buffer* pVertexBuffer, UINT InNumVertices, ID3D11Buffer* pIndexBuffer, UINT InNumIndices, UINT InStride);
	void Render();

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

	FLOAT ClearColor[4] = {0.1f, 0.1f, 0.1f, 1.0f };
};