#include "EnginePCH.h"
#include "GizmoRenderer.h"

#include "GeometryGenerator.h"

FGizmoRenderer::FGizmoRenderer()
{
}

bool FGizmoRenderer::Init(FRenderer* InRenderer)
{
	Renderer = InRenderer;
	FMeshData LocMeshData = FGeometryGenerator::CreateArrow(0.1f, 1.0f, 0.2f, 0.5f, 20, FVector4(1.0f, 0.0f, 0.0f, 1.0f));
	LocationMesh = MakeShared<FMesh>();
	LocationMesh->VertexBuffer = Renderer->CreateVertexBuffer(LocMeshData.Vertices.data(), sizeof(FVertex) * (UINT)LocMeshData.Vertices.size(), sizeof(FVertex));
	LocationMesh->IndexBuffer = Renderer->CreateIndexBuffer(LocMeshData.Indices.data(), LocMeshData.Indices.size());

	FMeshData RotMeshData = FGeometryGenerator::CreateRing(1.0f, 0.01f, 32, 16, FVector4(1.0f, 0.0f, 0.0f, 1.0f));
	RotationMesh = MakeShared<FMesh>();
	RotationMesh->VertexBuffer = Renderer->CreateVertexBuffer(RotMeshData.Vertices.data(), sizeof(FVertex) * (UINT)RotMeshData.Vertices.size(), sizeof(FVertex));
	RotationMesh->IndexBuffer = Renderer->CreateIndexBuffer(RotMeshData.Indices.data(), RotMeshData.Indices.size());

	FMeshData ScaleMeshData = FGeometryGenerator::CreateScaleBar(0.1f, 1.0f, 0.4f, 20, FVector4(1.0f, 0.0f, 0.0f, 1.0f));
	ScaleMesh = MakeShared<FMesh>();
	ScaleMesh->VertexBuffer = Renderer->CreateVertexBuffer(ScaleMeshData.Vertices.data(), sizeof(FVertex) * (UINT)ScaleMeshData.Vertices.size(), sizeof(FVertex));
	ScaleMesh->IndexBuffer = Renderer->CreateIndexBuffer(ScaleMeshData.Indices.data(), ScaleMeshData.Indices.size());

	FMeshData SphereData = FGeometryGenerator::CreateSphere(0.2f, 20, 10, FVector4(1.0f, 1.0f, 1.0f, 1.0f));
	SphereMesh = MakeShared<FMesh>();
	SphereMesh->VertexBuffer = Renderer->CreateVertexBuffer(SphereData.Vertices.data(), sizeof(FVertex) * (UINT)SphereData.Vertices.size(), sizeof(FVertex));
	SphereMesh->IndexBuffer = Renderer->CreateIndexBuffer(SphereData.Indices.data(), SphereData.Indices.size());

	CB = Renderer->CreateConstantBuffer(sizeof(FGizmoData));

	FGizmoData GizmoData;
	Transform.Rotation = FRotator(90.0f, 0.0f, 0.0f);
	World = Transform.GetWorldMatrix();
	GizmoData.World = World;
	GizmoData.World = GizmoData.World.GetTransposed();
	GizmoData.Color = FVector4(1.0f, 0.0f, 0.0f, 1.0f);

	AxisDataArray.push_back(GizmoData);

	Transform.Rotation = FRotator(0.0f, 0.0f, -90.0f);
	World = Transform.GetWorldMatrix();
	GizmoData.World = World;
	GizmoData.World = GizmoData.World.GetTransposed();
	GizmoData.Color = FVector4(0.0f, 1.0f, 0.0f, 1.0f);

	AxisDataArray.push_back(GizmoData);

	Transform.Rotation = FRotator(0.0f, 0.0f, 0.0f);
	World = Transform.GetWorldMatrix();
	GizmoData.World = World;
	GizmoData.World = GizmoData.World.GetTransposed();
	GizmoData.Color = FVector4(0.0f, 0.0f, 1.0f, 1.0f);

	AxisDataArray.push_back(GizmoData);

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION" , 0 , DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	Shader = Renderer->CreateShader(L"Shader/GizmoShader.hlsl", layout, 2);

	return false;
}

void FGizmoRenderer::OnRender(const FMatrix& ViewProj)
{

	Renderer->BindShader(Shader.get());
	Renderer->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	switch (Mode)
	{
	case EGizmoMode::Location:
	{
		Renderer->BindMesh(LocationMesh.get());

		FGizmoData Data{};
		for (int i = 0; i < 3;i++)
		{
			FGizmoData Data = AxisDataArray[i];
			Data.ViewProj = ViewProj.GetTransposed();
			Renderer->UpdateConstantBufferData(CB.get(), &Data, sizeof(FGizmoData));
			Renderer->BindConstantBuffer(0, CB.get(), EShaderBindFlagBits::Vertex);
			Renderer->DrawIndexed(LocationMesh->IndexBuffer->GetIndexCount());
		}

		Transform.Rotation = FRotator(0.0f, 0.0f, 0.0f);
		World = Transform.GetWorldMatrix();
		Data.World = World.GetTransposed();
		Data.ViewProj = ViewProj.GetTransposed();
		Data.Color = FVector4(1.0f, 1.0f, 1.0f, 1.0f);

		Renderer->BindMesh(SphereMesh.get());

		Renderer->UpdateConstantBufferData(CB.get(), &Data, sizeof(FGizmoData));
		Renderer->BindConstantBuffer(0, CB.get(), EShaderBindFlagBits::Vertex); 
		Renderer->DrawIndexed(SphereMesh->IndexBuffer->GetIndexCount());
		break;
	}
	case EGizmoMode::Rotation:
	{
		Renderer->BindMesh(RotationMesh.get());
		FGizmoData Data{};
		for (int i = 0; i < 3;i++)
		{
			FGizmoData Data = AxisDataArray[i];
			Data.ViewProj = ViewProj.GetTransposed();
			Renderer->UpdateConstantBufferData(CB.get(), &Data, sizeof(FGizmoData));
			Renderer->BindConstantBuffer(0, CB.get(), EShaderBindFlagBits::Vertex);
			Renderer->DrawIndexed(RotationMesh->IndexBuffer->GetIndexCount());
		}

		Transform.Rotation = FRotator(0.0f, 0.0f, 0.0f);
		World = Transform.GetWorldMatrix();
		Data.World = World.GetTransposed();
		Data.Color = FVector4(1.0f, 1.0f, 1.0f, 1.0f);

		Renderer->BindMesh(SphereMesh.get());

		Renderer->UpdateConstantBufferData(CB.get(), &Data, sizeof(FGizmoData));
		Renderer->BindConstantBuffer(0, CB.get(), EShaderBindFlagBits::Vertex);
		Renderer->DrawIndexed(SphereMesh->IndexBuffer->GetIndexCount());
		break;
	}
	case EGizmoMode::Scale:
	{
		Renderer->BindMesh(ScaleMesh.get());

		FGizmoData Data{};
		for (int i = 0; i < 3;i++)
		{
			FGizmoData Data = AxisDataArray[i];
			Data.ViewProj = ViewProj.GetTransposed();
			Renderer->UpdateConstantBufferData(CB.get(), &Data, sizeof(FGizmoData));
			Renderer->BindConstantBuffer(0, CB.get(), EShaderBindFlagBits::Vertex);
			Renderer->DrawIndexed(LocationMesh->IndexBuffer->GetIndexCount());
		}

		Transform.Rotation = FRotator(0.0f, 0.0f, 0.0f);
		World = Transform.GetWorldMatrix();
		Data.World = World.GetTransposed();
		Data.ViewProj = ViewProj.GetTransposed();
		Data.Color = FVector4(1.0f, 1.0f, 1.0f, 1.0f);

		Renderer->BindMesh(SphereMesh.get());

		Renderer->UpdateConstantBufferData(CB.get(), &Data, sizeof(FGizmoData));
		Renderer->BindConstantBuffer(0, CB.get(), EShaderBindFlagBits::Vertex);
		Renderer->DrawIndexed(SphereMesh->IndexBuffer->GetIndexCount());
		break;
	}
	default:
		break;
	}



	//Transform.Rotation = FRotator(00.0f, 0.0f, -90.0f);
	//World = Transform.GetWorldMatrix();
	//Data.World = World * ViewProj;
	//Data.World = Data.World.GetTransposed();
	//Data.Color = FVector4(0.0f, 1.0f, 0.0f, 1.0f);

	//Renderer->UpdateConstantBufferData(CB.get(), &Data, sizeof(FGizmoData));
	//Renderer->BindConstantBuffer(0, CB.get(), EShaderBindFlagBits::Vertex);
	//Renderer->DrawIndexed(LocationMesh->IndexBuffer->GetIndexCount());

	//Transform.Rotation = FRotator(0.0f, 0.0f, 0.0f);
	//World = Transform.GetWorldMatrix();
	//Data.World = World * ViewProj;
	//Data.World = Data.World.GetTransposed();
	//Data.Color = FVector4(0.0f, 0.0f, 1.0f, 1.0f);

	//Renderer->UpdateConstantBufferData(CB.get(), &Data, sizeof(FGizmoData));
	//Renderer->BindConstantBuffer(0, CB.get(), EShaderBindFlagBits::Vertex);
	//Renderer->DrawIndexed(LocationMesh->IndexBuffer->GetIndexCount());



}
