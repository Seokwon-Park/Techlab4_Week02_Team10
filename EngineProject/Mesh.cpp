#include "EnginePCH.h"
#include "Mesh.h"
#include "Renderer.h"

FMesh* FMesh::Create(void* InVertices, void* InIndices, uint32 InStride)
{
    Stride = InStride;
    VertexBuffer = FRenderer::GetInstance().CreateVertexBuffer(InVertices, Stride);
    IndexBuffer = FRenderer::GetInstance().CreateIndexBuffer(InIndices, Stride);
    return this;
}

ID3D11Buffer* FMesh::GetVertexBuffer()
{
    return VertexBuffer.Get();
}

ID3D11Buffer* FMesh::GetIndexBuffer()
{
    return IndexBuffer.Get();
}
