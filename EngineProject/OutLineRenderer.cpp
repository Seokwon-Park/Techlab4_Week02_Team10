#include "EnginePCH.h"
#include "OutLineRenderer.h"
#include "ResourceManager.h"

void FOutlineRenderer::Init(FRenderer* InRenderer)
{
	Renderer = InRenderer;
	Shader = FResourceManager::GetInstance().GetShader("OutlineShader.hlsl");
	D3D11_RASTERIZER_DESC RasterizerDesc = {};
	RasterizerDesc.FillMode = D3D11_FILL_SOLID;
	RasterizerDesc.CullMode = D3D11_CULL_FRONT;
	RasterizerDesc.FrontCounterClockwise = FALSE;
	Renderer->GetDevice()->CreateRasterizerState(&RasterizerDesc, &RasterizerState);

	//auto Data = FGeometryGenerator::CreateSphere(1.0f, 20, 10, FVector4(1.0f, 0.0f, 0.0f, 1.0f));
	//Test = MakeShared<FMesh>();
	//Test->VertexBuffer = Renderer->CreateVertexBuffer(Data.Vertices.data(), sizeof(FVertex) * (UINT)Data.Vertices.size(), sizeof(FVertex));
	//Test->IndexBuffer = Renderer->CreateIndexBuffer(Data.Indices.data(), Data.Indices.size());
}

void FOutlineRenderer::SetMesh(FMesh* InMesh)
{
	Mesh = InMesh;
}

void FOutlineRenderer::OnRender(const FOutline& InOutline, const FMatrix& InViewProj) 
{
	if (!InOutline.GetTarget())
	{
		return;
	}


	Renderer->GetDeviceContext()->RSSetState(RasterizerState.Get());
	Renderer->BindShader(Shader);
	Renderer->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	Renderer->BindMesh(InOutline.GetMesh());

	FMatrix MVP = InOutline.GetWorldMatrix() * InViewProj;
	Renderer->UpdateConstantBuffer(MVP);
	Renderer->DrawIndexed(InOutline.GetMesh()->IndexBuffer->GetIndexCount());
}
