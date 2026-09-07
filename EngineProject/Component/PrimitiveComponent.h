#pragma once

#include "SceneComponent.h"
#include "../Shader.h"
#include "../Mesh.h"
#include "RenderPacket.h"

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
	
	void SetMeshShader(TSharedPtr<FMesh> InMesh, FShader* InShader) { Mesh = InMesh; Shader = InShader; }
	void SubmitToRenderQueue(TQueue<FRenderPacket>& RenderQueue);

	EPrimitiveType GetType() const { return Type; }
protected:
	EPrimitiveType Type = EPrimitiveType::None;
	FShader* Shader = nullptr;
	TSharedPtr<FMesh> Mesh = nullptr;
};