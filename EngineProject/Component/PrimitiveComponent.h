#pragma once

#include "SceneComponent.h"
#include "../Shader.h"
#include "../Mesh.h"
#include "RenderPacket.h"

enum class EPrimitiveType
{
	Sphere,
	Cube
};

class UPrimitiveComponent :public USceneComponent
{
	DECLARE_CLASS(UPrimitiveComponent, USceneComponent)

	REFLECT_START(ClassName)
		REFLECT_END()
public:
	void SubmitToRenderQueue(TQueue<FRenderPacket>& RenderQueue);

	EPrimitiveType GetType() const { return Type; }
private:
	EPrimitiveType Type;
	TSharedPtr<FShader> Shader;
	TSharedPtr<FMesh> Mesh;
};