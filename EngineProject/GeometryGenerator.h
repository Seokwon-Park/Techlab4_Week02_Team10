#pragma once

#include "Render/Vertex.h"

struct FMeshData
{
	TArray<FVertex> Vertices;
	TArray<uint32> Indices;
};

class FGeometryGenerator
{
public:
	static FMeshData CreateLine(const FVector& Start, const FVector& End, const FVector4& Color);
	static FMeshData CreateAxis();

	static FMeshData CreateCone(float Radius, float Height, int Segments, const FVector4& Color);
	static FMeshData CreateCylinder(float Radius, float Height, int Segments, const FVector4& Color);
	static FMeshData CreateArrow(float Length, float HeadSize, const FVector4& Color); // Cylinder + Cone 합성
	static FMeshData CreateRing(float Radius, int Segments, const FVector4& Color);    // 회전 기즈모용
	static FMeshData CreateCube(float Size, const FVector4& Color = FVector4(1.0f, 1.0f, 1.0f, 1.0f));

	static FMeshData CreateSphere(float _radius, uint32 _numSlices, uint32 _numStacks);

};