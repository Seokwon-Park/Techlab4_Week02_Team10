#include "EnginePCH.h"
#include "GridRenderer.h"

#include "Render/Vertex.h"

FGridRenderer::~FGridRenderer()
{
}

bool FGridRenderer::Init(FRenderer* InRenderer)
{
	Renderer = InRenderer;
	TArray<FVertex> Vertices =
	{
		// X Axis
		{{0.0f, 0.0f, 0.0f}, {0.85f, 0.20f, 0.20f, 1.0f}},
		{{100.0f, 0.0f, 0.0f}, {0.85f, 0.20f, 0.20f, 1.0f}},

		// Y Axis
		{{0.0f, 0.0f, 0.0f}, {0.25f, 0.80f, 0.35f, 1.0f}},
		{{0.0f, 100.0f, 0.0f}, {0.25f, 0.80f, 0.35f, 1.0f}},

		// Z Axis
		{{0.0f, 0.0f, 0.0f}, {0.25f, 0.45f, 0.90f, 1.0f}},
		{{0.0f, 0.0f, 100.0f}, {0.25f, 0.45f, 0.90f, 1.0f}},
	};

	TArray<uint32> Indices =
	{
		0,1,2,3,4,5
	};

	VB = Renderer->CreateVertexBuffer(Vertices.data(), sizeof(FVertex) * Vertices.size(), sizeof(FVertex));
	IB = Renderer->CreateIndexBuffer(Indices.data(), sizeof(uint32) * Indices.size());

	return false;
}

void FGridRenderer::OnRender(const FMatrix& World, const FMatrix& ViewProj)
{
	Renderer->BindVertexBuffer(VB.get());
	Renderer->BindIndexBuffer(IB.get());
	Renderer->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	Renderer->UpdateConstantBuffer(World * ViewProj);
	Renderer->DrawIndexed(6);
}
