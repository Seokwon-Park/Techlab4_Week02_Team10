#include "EnginePCH.h"
#include "OutLineRenderer.h"
#include "ResourceManager.h"

void FOutlineRenderer::Init(FRenderer* InRenderer)
{
    Renderer = InRenderer;
    FResourceManager::GetInstance().GetShader("Shader/OutlineShader.hlsl");
    D3D11_RASTERIZER_DESC RasterizerDesc = {};
    RasterizerDesc.FillMode = D3D11_FILL_SOLID;
    RasterizerDesc.CullMode = D3D11_CULL_FRONT;
    RasterizerDesc.FrontCounterClockwise = FALSE;
    RasterizerDesc.DepthClipEnable = TRUE;
    Renderer->GetDevice()->CreateRasterizerState(&RasterizerDesc, &RasterizerState);
}

void FOutlineRenderer::SetMesh(TSharedPtr<FMesh>& InMesh)
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
    Renderer->BindShader(Shader.get());
    Renderer->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
   
    Renderer->BindMesh(InOutline.GetMesh());
    FMatrix MVP = InOutline.GetWorldMatrix() * InViewProj;
    Renderer->UpdateConstantBuffer(MVP);
    Renderer->DrawIndexed(InOutline.GetMesh()->IndexBuffer->GetIndexCount());
}
