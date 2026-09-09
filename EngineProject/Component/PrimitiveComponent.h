#pragma once

#include "SceneComponent.h"
#include "../Shader.h"
#include "../Mesh.h"
#include "RenderPacket.h"
#include "GeometryGenerator.h"

enum class EPrimitiveType
{
	None,
	Sphere,
	Cube
};

class UPrimitiveComponent :public USceneComponent
{
	DECLARE_CLASS(UPrimitiveComponent, USceneComponent)

	REFLECT_START(ClassName)
		REFLECT_END()
public:
	virtual void BeginPlay() override;

	void SetMeshData(const FMeshData& data) { MeshData = data; }
	void SetMeshShader(TSharedPtr<FMesh> InMesh, FShader* InShader) { Mesh = InMesh; Shader = InShader; }
	void SubmitToRenderQueue(TQueue<FRenderPacket>& RenderQueue);

	FMeshData GetMeshData() const { return MeshData; }
	void SetMesh(FMesh* InMesh);
	TSharedPtr<FMesh> GetMesh() const { return Mesh; };
	FShader* GetShader() const { return Shader; };

	void SetType(EPrimitiveType Ptype) { Type = Ptype; }
	EPrimitiveType GetType() const { return Type; }
protected:
	EPrimitiveType Type = EPrimitiveType::None;
	FShader* Shader = nullptr;
	TSharedPtr<FMesh> Mesh = nullptr;
	FMeshData MeshData;
};