#include "EnginePCH.h"
#include "Renderer.h"
#include "Shader.h"
#include "Mesh.h"

void FRenderer::BeginFrame()
{
	DeviceContext->ClearRenderTargetView(FrameBufferRTV.Get(), ClearColor);
	DeviceContext->ClearDepthStencilView(FrameBufferDSV.Get(), D3D11_CLEAR_DEPTH, 0.0f, 0);
	DeviceContext->OMSetRenderTargets(1, FrameBufferRTV.GetAddressOf(), FrameBufferDSV.Get());
	DeviceContext->RSSetViewports(1, &ViewportInfo);
}

void FRenderer::EndFrame()
{
	SwapChain->Present(1, 0);
}

void FRenderer::Create(HWND hWindow)
{
	CreateDeviceAndSwapChain(hWindow);

	CreateFrameBuffer();

	CreateRasterizerState();
	CreateDepthStencilBufferAndState();
	CreateConstantBuffer();

	// 임시 셰이더 프로그램 컴파일 로직
	/*D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION" , 0 , DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	FShader* shader = CreateShader(L"Shader/DefaultShader.hlsl", layout, 2);

	DeviceContext->VSSetShader(shader->VertexShader.Get(), nullptr, 0);
	DeviceContext->PSSetShader(shader->PixelShader.Get(), nullptr, 0);
	DeviceContext->IASetInputLayout(shader->InputLayout.Get());*/
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
	SwapChain->GetBuffer(0, IID_PPV_ARGS(FrameBuffer.GetAddressOf()));
	Device->CreateRenderTargetView(FrameBuffer.Get(), nullptr, FrameBufferRTV.GetAddressOf());
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
	DepthDesc.Format = DXGI_FORMAT_D32_FLOAT;	// 24비트 깊이, 8비트 스텐실
	DepthDesc.SampleDesc.Count = 1;
	DepthDesc.SampleDesc.Quality = 0;
	DepthDesc.Usage = D3D11_USAGE_DEFAULT;
	DepthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	DepthDesc.CPUAccessFlags = 0;
	DepthDesc.MiscFlags = 0;
	HRESULT hr = Device->CreateTexture2D(&DepthDesc, NULL, DepthStencilBuffer.GetAddressOf());

	Device->CreateDepthStencilView(DepthStencilBuffer.Get(), nullptr, FrameBufferDSV.GetAddressOf());

	D3D11_DEPTH_STENCIL_DESC DepthStencilDesc;

	// Depth test Paramiter
	DepthStencilDesc.DepthEnable = true;
	DepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	DepthStencilDesc.DepthFunc = D3D11_COMPARISON_GREATER;

	// Stencil test Paramiter
	DepthStencilDesc.StencilEnable = false;
	DepthStencilDesc.StencilReadMask = 0xFF;
	DepthStencilDesc.StencilWriteMask = 0xFF;

	DepthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	DepthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	DepthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	DepthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	Device->CreateDepthStencilState(&DepthStencilDesc, DepthStencilState.GetAddressOf());
}

void FRenderer::CreateConstantBuffer()
{
	D3D11_BUFFER_DESC constantbufferdesc = {};

	constantbufferdesc.ByteWidth = sizeof(FConstants) + 0xf & 0xfffffff0;
	constantbufferdesc.Usage = D3D11_USAGE_DYNAMIC;	// will be updated from CPU every frame
	constantbufferdesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constantbufferdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	Device->CreateBuffer(&constantbufferdesc, nullptr, &ConstantBuffer);
}

ID3D11DeviceContext* FRenderer::GetDeviceContext()
{
	return DeviceContext.Get();
}


FShader* FRenderer::CreateShader(const wchar_t* FileName, D3D11_INPUT_ELEMENT_DESC* InLayoutDesc, size_t InLayoutSize)
{
	FShader* shader = new FShader;

	ID3DBlob* VertexShaderCSO;

	ID3DBlob* ErrorBlob;
	HRESULT hr = D3DCompileFromFile(FileName, nullptr, nullptr, "mainVS", "vs_5_0", 0, 0, &VertexShaderCSO, &ErrorBlob);
	
	Device->CreateVertexShader(VertexShaderCSO->GetBufferPointer(), VertexShaderCSO->GetBufferSize(), nullptr, shader->VertexShader.GetAddressOf());

	ID3DBlob* PixelShaderCSO;
	D3DCompileFromFile(FileName, nullptr, nullptr, "mainPS", "ps_5_0", 0, 0, &PixelShaderCSO, nullptr);
	Device->CreatePixelShader(PixelShaderCSO->GetBufferPointer(), PixelShaderCSO->GetBufferSize(), nullptr, shader->PixelShader.GetAddressOf());

	hr = Device->CreateInputLayout(InLayoutDesc, InLayoutSize,
		VertexShaderCSO->GetBufferPointer(), VertexShaderCSO->GetBufferSize(), &(shader->InputLayout));

	VertexShaderCSO->Release();
	PixelShaderCSO->Release();

	return shader;
}

TSharedPtr<FMesh> FRenderer::CreateMesh(TSharedPtr<FVertexBuffer> VertexBuffer, TSharedPtr<FIndexBuffer> IndexBuffer)
{
	TSharedPtr<FMesh> Mesh = MakeShared<FMesh>();
	
	Mesh->VertexBuffer = VertexBuffer;
	Mesh->IndexBuffer = IndexBuffer;

	return Mesh;
}


TSharedPtr<FVertexBuffer> FRenderer::CreateVertexBuffer(const void* InVertices, uint32 TotalSize, uint32 Stride)
{
	TSharedPtr<FVertexBuffer> Buffer = MakeShared<FVertexBuffer>(Device.Get(), InVertices, TotalSize, Stride);

	return Buffer;
}

TSharedPtr<FIndexBuffer> FRenderer::CreateIndexBuffer(const uint32* InIndices, uint32 IndexCount)
{
	TSharedPtr<FIndexBuffer> Buffer = MakeShared<FIndexBuffer>(Device.Get(), InIndices, IndexCount);

	return Buffer;
}

void FRenderer::UpdateConstantBuffer(const FMatrix& MVP)
{
	if (ConstantBuffer)
	{
		D3D11_MAPPED_SUBRESOURCE constantbufferMSR;
		FConstants constants;
		DeviceContext->Map(ConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &constantbufferMSR);
		FConstants* constant = (FConstants*)constantbufferMSR.pData;
		{
			FMatrix TransMVP = MVP.GetTransposed();
			constant->MVP = TransMVP;
		}
		DeviceContext->Unmap(ConstantBuffer.Get(), 0);
		DeviceContext->VSSetConstantBuffers(0, 1, ConstantBuffer.GetAddressOf());
	}
}

void FRenderer::BindVertexBuffer(FVertexBuffer* VertexBuffer)
{
	uint32 offset = 0;
	uint32 Stride = VertexBuffer->GetStride();
	ID3D11Buffer* Buffer = VertexBuffer->GetBuffer();
	DeviceContext->IASetVertexBuffers(0, 1, &Buffer, &Stride, &offset);
}

void FRenderer::BindIndexBuffer(FIndexBuffer* IndexBuffer)
{
	DeviceContext->IASetIndexBuffer(IndexBuffer->GetBuffer(), DXGI_FORMAT_R32_UINT, 0);
}

void FRenderer::SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology)
{
	DeviceContext->IASetPrimitiveTopology(Topology);
}

void FRenderer::BindShader(FShader* InShader)
{
	DeviceContext->VSSetShader(InShader->VertexShader.Get(), nullptr, 0);
	DeviceContext->PSSetShader(InShader->PixelShader.Get(), nullptr, 0);
	DeviceContext->IASetInputLayout(InShader->InputLayout.Get());
}

void FRenderer::BindMesh(FMesh* InMesh)
{
	BindVertexBuffer(InMesh->VertexBuffer.get());
	BindIndexBuffer(InMesh->IndexBuffer.get());
}

void FRenderer::DrawIndexed(int IndexCount)
{
	DeviceContext->OMSetDepthStencilState(DepthStencilState.Get(), 1);
	DeviceContext->DrawIndexed(IndexCount, 0, 0);
}

void FRenderer::Prepare()
{
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DeviceContext->OMSetRenderTargets(1, FrameBufferRTV.GetAddressOf(), nullptr);
	DeviceContext->RSSetViewports(1, &ViewportInfo);
	DeviceContext->RSSetState(RasterizerState.Get());
	DeviceContext->OMSetBlendState(nullptr, nullptr, 0xffff'ffff);


}


void FRenderer::RenderAll(TQueue<FRenderPacket>& InQueue, FMatrix VP)
{
	//DeviceContext->OMSetBlendState(nullptr, nullptr, 0xffff'ffff);
	//DeviceContext->OMSetDepthStencilState(nullptr, 0);
	while (true)
	{
		if (InQueue.empty())
		{
			return;
		}

		FRenderPacket rp = InQueue.front();

		BindShader(rp.shader);
		BindMesh(rp.mesh);

		// rp.Transform 과 Camera VP 행렬 곱
		// 행렬곱의 결과 (MVP Matrix) Constant Buffer 업데이트 필요
		FMatrix MVP;
		MVP = rp.model * VP;
		UpdateConstantBuffer(MVP);
		SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		DrawIndexed(rp.mesh->IndexBuffer->GetIndexCount());

		InQueue.pop();
	}
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