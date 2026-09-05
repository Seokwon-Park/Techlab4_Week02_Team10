#pragma once

#include "SceneComponent.h"
#include "../Shader.h"
#include "../Mesh.h"

enum class EPrimitiveType
{
	Sphere,
	Cube
};

class UPrimitiveComponent :public USceneComponent
{
	DECLARE_CLASS(UPrimitiveComponent, USceneComponent)
public:
	void Render();

	EPrimitiveType GetType() const { return Type; }
private:
	EPrimitiveType Type;
	TSharedPtr<FShader> Shader;
	TSharedPtr<FMesh> Mesh;
};