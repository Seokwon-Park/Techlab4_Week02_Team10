#pragma once

#include "Render/Vertex.h"

struct FMeshData
{
	TArray<FVertex> Vertices;
	TArray<uint32> Indices;

	void GetAABB(FVector& OutBoxMin, FVector& OutBoxMax)
	{
		if (Vertices.size() == 0)
		{
			OutBoxMax = { 0.0f, 0.0f, 0.0f };
			OutBoxMin = { 0.0f, 0.0f, 0.0f };

			return;
		}

		FVector Min{ FLT_MAX, FLT_MAX, FLT_MAX };
		FVector Max{ -FLT_MAX, -FLT_MAX, -FLT_MAX };
		for (const FVertex& vertex : Vertices)
		{
			Min.X = fmin(Min.X, vertex.Position.X);
			Min.Y = fmin(Min.Y, vertex.Position.Y);
			Min.Z = fmin(Min.Z, vertex.Position.Z);

			Max.X = fmax(Max.X, vertex.Position.X);
			Max.Y = fmax(Max.Y, vertex.Position.Y);
			Max.Z = fmax(Max.Z, vertex.Position.Z);
		}
		OutBoxMin = Min;
		OutBoxMax = Max;
	}
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