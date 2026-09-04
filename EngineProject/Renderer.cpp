#include "Renderer.h"

void Renderer::Create(HWND hWindow)
{
	CreateDeviceAndSwapChain(hWindow);

	CreateFrameBuffer();

	CreateRasterizerState();
}


void Renderer::CreateDeviceAndSwapChain(HWND hWindow)
{
	D3D_FEATURE_LEVEL FeatureLevels[] = { D3D_FEATURE_LEVEL_11_0 };

	DXGI_SWAP_CHAIN_DESC SwapChainDesc = {};
	SwapChainDesc.BufferDesc.Width = 0;
	SwapChainDesc.BufferDesc.Height = 0;

	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; 
	SwapChainDesc.SampleDesc.Count = 1;
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.BufferCount = 2;
	SwapChainDesc.OutputWindow = hWindow;
	SwapChainDesc.Windowed = TRUE;
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

	D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
		D3D11_CREATE_DEVICE_BGRA_SUPPORT,
		FeatureLevels, ARRAYSIZE(FeatureLevels), D3D11_SDK_VERSION,
		&SwapChainDesc, &SwapChain, &Device, nullptr, &DeviceContext);

	SwapChain->GetDesc(&SwapChainDesc);

	ViewportInfo = { 0.0f, 0.0f,
		(float)SwapChainDesc.BufferDesc.Width, (float)SwapChainDesc.BufferDesc.Height,
		0.0f, 1.0f };
}


void Renderer::CreateFrameBuffer()
{
	SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&FrameBuffer);

	D3D11_RENDER_TARGET_VIEW_DESC FrameBufferRTVDesc = {};
	FrameBufferRTVDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
	FrameBufferRTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	Device->CreateRenderTargetView(FrameBuffer.Get(), &FrameBufferRTVDesc, &FrameBufferRTV);
}


void Renderer::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC RasterizerDesc = {};
	RasterizerDesc.FillMode = D3D11_FILL_SOLID;
	RasterizerDesc.CullMode = D3D11_CULL_BACK;

	Device->CreateRasterizerState(&RasterizerDesc, &RasterizerState);
}


void Renderer::SwapBuffer()
{
	SwapChain->Present(1, 0);
}


void Renderer::Shutdown()
{
	if (DeviceContext)
	{
		DeviceContext->ClearState();
		DeviceContext->Flush();
	}
}