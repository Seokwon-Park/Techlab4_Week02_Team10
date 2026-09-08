#include "EnginePCH.h"
#include "GizmoRenderer.h"

#include "GeometryGenerator.h"

FGizmoRenderer::FGizmoRenderer()
{
}

bool FGizmoRenderer::Init(FRenderer* InRenderer)
{
	Renderer = InRenderer;
	FMeshData Data = FGeometryGenerator::CreateArrow(0.1f, 1.0f, 0.2f, 0.5f, 20, FVector4(1.0f, 0.0f, 0.0f, 1.0f));
	ArrowMesh = MakeShared<FMesh>();
	ArrowMesh->VertexBuffer = Renderer->CreateVertexBuffer(Data.Vertices.data(), sizeof(FVertex) * (UINT)Data.Vertices.size(), sizeof(FVertex));
	ArrowMesh->IndexBuffer = Renderer->CreateIndexBuffer(Data.Indices.data(), Data.Indices.size());

	FMeshData SphereData = FGeometryGenerator::CreateSphere(0.2f, 20, 10, FVector4(1.0f, 1.0f, 1.0f, 1.0f));
	//FMeshData SphereData = FGeometryGenerator::CreateCube(2.0f, FVector4(0.0f, 0.0f, 0.0f, 1.0f));
	SphereMesh = MakeShared<FMesh>();
	SphereMesh->VertexBuffer = Renderer->CreateVertexBuffer(SphereData.Vertices.data(), sizeof(FVertex) * (UINT)SphereData.Vertices.size(), sizeof(FVertex));
	SphereMesh->IndexBuffer = Renderer->CreateIndexBuffer(SphereData.Indices.data(), SphereData.Indices.size());

	return false;
}

void FGizmoRenderer::OnRender(const FMatrix& ViewProj)
{
	Renderer->BindMesh(ArrowMesh.get());
	Renderer->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	Transform.Rotation = FRotator(0.0f, 90.0f, 0.0f);
	World = Transform.GetWorldMatrix();
	Renderer->UpdateConstantBuffer(World * ViewProj);
	Renderer->DrawIndexed(ArrowMesh->IndexBuffer->GetIndexCount());

	Transform.Rotation = FRotator(00.0f, 0.0f, 90.0f);
	World = Transform.GetWorldMatrix();
	Renderer->UpdateConstantBuffer(World * ViewProj);
	Renderer->DrawIndexed(ArrowMesh->IndexBuffer->GetIndexCount());

	Transform.Rotation = FRotator(0.0f, 0.0f, 0.0f);
	World = Transform.GetWorldMatrix();
	Renderer->UpdateConstantBuffer(World * ViewProj);
	Renderer->DrawIndexed(ArrowMesh->IndexBuffer->GetIndexCount());

	Renderer->BindMesh(SphereMesh.get());
	Renderer->UpdateConstantBuffer(World * ViewProj);
	Renderer->DrawIndexed(SphereMesh->IndexBuffer->GetIndexCount());


}
