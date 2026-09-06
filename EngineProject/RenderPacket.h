#pragma once
#include "Transform.h"
#include "Mesh.h"
#include "Shader.h"

struct FRenderPacket {
	FTransform transform;
	FMesh* mesh;
	FShader* shader;
};