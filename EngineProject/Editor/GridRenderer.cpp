#include "EnginePCH.h"
#include "GridRenderer.h"

#include "Render/Vertex.h"

FGridRenderer::~FGridRenderer()
{
	VB->Release();
	IB->Release();
}

bool FGridRenderer::Init()
{
	TArray<FVertex> Vertices =
	{
		// X Axis
		{{0.0f, 0.0f, 0.0f}, {0.85f, 0.20f, 0.20f, 1.0f}},
		{{1.0f, 0.0f, 0.0f}, {0.85f, 0.20f, 0.20f, 1.0f}},

		// Y Axis
		{{0.0f, 0.0f, 0.0f}, {0.25f, 0.80f, 0.35f, 1.0f}},
		{{0.0f, 1.0f, 0.0f}, {0.25f, 0.80f, 0.35f, 1.0f}},

		// Z Axis
		{{0.0f, 0.0f, 0.0f}, {0.25f, 0.45f, 0.90f, 1.0f}},
		{{0.0f, 0.0f, 1.0f}, {0.25f, 0.45f, 0.90f, 1.0f}},
	};

	TArray<uint32> Indices =
	{
		0,1,2,3,4,5
	};

	VB = Renderer->CreateVertexBuffer(Vertices.data(), sizeof(FVertex));
	IB = Renderer->CreateIndexBuffer(Indices.data(), sizeof(uint32));



	return false;
}

void FGridRenderer::OnRender()
{
}
