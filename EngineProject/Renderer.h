#pragma once
#pragma comment(lib, "user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl/client.h>

class FShader;

class FRenderer
{
public:
	void Create(HWND hWindow);

	void CreateDeviceAndSwapChain(HWND hWindow);
	void CreateFrameBuffer();
	void CreateRasterizerState();
	void CreateDepthStencilBufferAndState();
	void SwapBuffer();

	void CreateShader(FShader* InShader, D3D11_INPUT_ELEMENT_DESC* InLayoutDesc, size_t InLayoutSize);

	void Prepare();
	void RenderPrimitive(ID3D11Buffer* pBuffer, UINT InStride, UINT InNumVertices);
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