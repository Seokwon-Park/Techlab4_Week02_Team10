#include "EnginePCH.h"
#include "Renderer.h"
#include "Shader.h"

FRenderer& FRenderer::GetInstance()
{
	static FRenderer Renderer;
	return Renderer;
}

void FRenderer::Create(HWND hWindow)
{
	CreateDeviceAndSwapChain(hWindow);

	CreateFrameBuffer();

	CreateRasterizerState();
	CreateDepthStencilBufferAndState();

	// 임시 셰이더 프로그램 컴파일 로직
	FShader* shader = new FShader;
	shader->Init(L"Shader/DefaultShader.hlsl", "mainVS", "mainPS", sizeof(FVertexSimple));
	shader->Create(&(FRenderer::GetInstance()));

	DeviceContext->VSSetShader(shader->VertexShader.Get(), nullptr, 0);
	DeviceContext->PSSetShader(shader->PixelShader.Get(), nullptr, 0);
	DeviceContext->IASetInputLayout(shader->InputLayout.Get());
}


void FRenderer::CreateDeviceAndSwapChain(HWND hWindow)
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
		&SwapChainDesc, SwapChain.GetAddressOf(), Device.GetAddressOf(), nullptr, DeviceContext.GetAddressOf());

	SwapChain->GetDesc(&SwapChainDesc);

	ViewportInfo = { 0.0f, 0.0f,
		(float)SwapChainDesc.BufferDesc.Width, (float)SwapChainDesc.BufferDesc.Height,
		0.0f, 1.0f };
}

void FRenderer::CreateFrameBuffer()
{
	SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)FrameBuffer.GetAddressOf());

	D3D11_RENDER_TARGET_VIEW_DESC FrameBufferRTVDesc = {};
	FrameBufferRTVDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
	FrameBufferRTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	Device->CreateRenderTargetView(FrameBuffer.Get(), &FrameBufferRTVDesc, FrameBufferRTV.GetAddressOf());
}


void FRenderer::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC RasterizerDesc = {};
	RasterizerDesc.FillMode = D3D11_FILL_SOLID;
	RasterizerDesc.CullMode = D3D11_CULL_BACK;

	Device->CreateRasterizerState(&RasterizerDesc, &RasterizerState);
}

void FRenderer::CreateDepthStencilBufferAndState()
{
	D3D11_TEXTURE2D_DESC DepthDesc;

	DepthDesc.Width = ViewportInfo.Width;
	DepthDesc.Height = ViewportInfo.Height;

	DepthDesc.MipLevels = 1;
	DepthDesc.ArraySize = 1;
	DepthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;	// 24비트 깊이, 8비트 스텐실
	DepthDesc.SampleDesc.Count = 1;
	DepthDesc.SampleDesc.Quality = 0;
	DepthDesc.Usage = D3D11_USAGE_DEFAULT;
	DepthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	DepthDesc.CPUAccessFlags = 0;
	DepthDesc.MiscFlags = 0;
	HRESULT hr = Device->CreateTexture2D(&DepthDesc, NULL, DepthStencilBuffer.GetAddressOf());

	D3D11_DEPTH_STENCIL_DESC DepthStencilDesc;

	// Depth test Paramiter
	DepthStencilDesc.DepthEnable = true;
	DepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	DepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	// Stencil test Paramiter
	DepthStencilDesc.StencilEnable = true;
	DepthStencilDesc.StencilReadMask = 0xFF;
	DepthStencilDesc.StencilWriteMask = 0xFF;

	DepthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	DepthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	DepthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	DepthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	Device->CreateDepthStencilState(&DepthStencilDesc, DepthStencilState.GetAddressOf());
}


void FRenderer::SwapBuffer()
{
	SwapChain->Present(1, 0);
}

void FRenderer::CreateShader(FShader* InShader, D3D11_INPUT_ELEMENT_DESC* InLayoutDesc, size_t InLayoutSize)
{
	ID3DBlob* VertexShaderCSO;

	ID3DBlob* ErrorBlob;
	HRESULT hr = D3DCompileFromFile(InShader->File, nullptr, nullptr, "mainVS", "vs_5_0", 0, 0, &VertexShaderCSO, &ErrorBlob);
	
	Device->CreateVertexShader(VertexShaderCSO->GetBufferPointer(), VertexShaderCSO->GetBufferSize(), nullptr, InShader->VertexShader.GetAddressOf());

	ID3DBlob* PixelShaderCSO;
	D3DCompileFromFile(InShader->File, nullptr, nullptr, InShader->PixelFunctionName, "ps_5_0", 0, 0, &PixelShaderCSO, nullptr);
	Device->CreatePixelShader(PixelShaderCSO->GetBufferPointer(), PixelShaderCSO->GetBufferSize(), nullptr, InShader->PixelShader.GetAddressOf());

	hr = Device->CreateInputLayout(InLayoutDesc, InLayoutSize,
		VertexShaderCSO->GetBufferPointer(), VertexShaderCSO->GetBufferSize(), &(InShader->InputLayout));

	VertexShaderCSO->Release();
	PixelShaderCSO->Release();
}

ID3D11Buffer* FRenderer::CreateVertexBuffer(void* InVertices, UINT InByteWidth)
{
	// Create a vertex buffer
	D3D11_BUFFER_DESC vertexbufferdesc = {};
	vertexbufferdesc.ByteWidth = InByteWidth;
	vertexbufferdesc.Usage = D3D11_USAGE_IMMUTABLE;
	vertexbufferdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA vertexbufferSRD = { InVertices };

	ID3D11Buffer* vertexBuffer;

	HRESULT hr = Device->CreateBuffer(&vertexbufferdesc, &vertexbufferSRD, &vertexBuffer);

	return vertexBuffer;
}

ID3D11Buffer* FRenderer::CreateIndexBuffer(void* InIndices, UINT InByteWidth)
{
	// Create a vertex buffer
	D3D11_BUFFER_DESC vertexbufferdesc = {};
	vertexbufferdesc.ByteWidth = InByteWidth;
	vertexbufferdesc.Usage = D3D11_USAGE_IMMUTABLE;
	vertexbufferdesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA vertexbufferSRD = { InIndices };

	ID3D11Buffer* vertexBuffer;

	HRESULT hr = Device->CreateBuffer(&vertexbufferdesc, &vertexbufferSRD, &vertexBuffer);

	return vertexBuffer;
}

void FRenderer::Prepare()
{
	DeviceContext->ClearRenderTargetView(FrameBufferRTV.Get(), ClearColor);

	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	DeviceContext->RSSetViewports(1, &ViewportInfo);

	DeviceContext->RSSetState(RasterizerState.Get());

	DeviceContext->OMSetRenderTargets(1, FrameBufferRTV.GetAddressOf(), nullptr);

	DeviceContext->OMSetBlendState(nullptr, nullptr, 0xffff'ffff);

	DeviceContext->OMSetDepthStencilState(DepthStencilState.Get(), 1);

	// 임시 버텍스 버퍼 생성 로직
	/*FVertexSimple Triangle[]
	{
		{0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f},
		{ 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f },
		{ -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f }
	};

	ID3D11Buffer* vertexBuffer = FRenderer::GetInstance().CreateVertexBuffer(Triangle, sizeof(Triangle));
	FRenderer::GetInstance().RenderPrimitive(vertexBuffer, sizeof(FVertexSimple), sizeof(Triangle)/sizeof(FVertexSimple));*/
}

void FRenderer::RenderPrimitive(ID3D11Buffer* pBuffer, UINT InStride, UINT InNumVertices)
{
	UINT offset = 0;
	DeviceContext->IASetVertexBuffers(0, 1, &pBuffer, &InStride, &offset);
	DeviceContext->Draw(InNumVertices, 0);
}

void FRenderer::Render()
{
	SwapBuffer();
}


void FRenderer::Shutdown()
{
	DeviceContext->OMSetRenderTargets(0, nullptr, nullptr);
	if (DeviceContext)
	{
		DeviceContext->ClearState();
		DeviceContext->Flush();
	}
}