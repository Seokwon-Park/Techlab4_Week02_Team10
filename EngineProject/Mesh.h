#pragma once

#include "Buffer.h"

struct FMesh
{
	TSharedPtr<FVertexBuffer> VertexBuffer;
	TSharedPtr<FIndexBuffer> IndexBuffer;
};