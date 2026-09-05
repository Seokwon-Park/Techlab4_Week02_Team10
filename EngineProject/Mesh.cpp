#include "EnginePCH.h"
#include "Mesh.h"
#include "Renderer.h"

FMesh* FMesh::Create(void* InVertices, uint32 InNumVertices, void* InIndices, uint32 InNumIndices, uint32 InStride)
{
    Stride = InStride;
    NumVertices = InNumVertices;
    NumIndices = InNumIndices;
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
