#include "EnginePCH.h"
#include "GeometryGenerator.h"

FMeshData FGeometryGenerator::CreateCube(float Size, const FVector4& Color)
{
	float HalfWidth = Size / 2.0f;
	float HalfHeight = Size / 2.0f;
	float HalfDepth = Size / 2.0f;

	TArray<FVector> positions =
	{
		//Front
		FVector(-HalfWidth, -HalfHeight, -HalfDepth),
		FVector(-HalfWidth, HalfHeight, -HalfDepth),
		FVector(HalfWidth, HalfHeight, -HalfDepth),
		FVector(HalfWidth, -HalfHeight, -HalfDepth),
		//Back
		FVector(-HalfWidth, -HalfHeight, HalfDepth),
		FVector(-HalfWidth, HalfHeight, HalfDepth),
		FVector(HalfWidth, HalfHeight, HalfDepth),
		FVector(HalfWidth, -HalfHeight, HalfDepth)
	};

	TArray<FVector> normals =
	{
		FVector(0.0f,0.0f,-1.0f),//Front
		FVector(0.0f,0.0f,1.0f), //Back
		FVector(0.0f,1.0f,0.0f), //Top
		FVector(0.0f,-1.0f,0.0f),//Bottom
		FVector(-1.0f,0.0f,0.0f),//Left
		FVector(1.0f,0.0f,0.0f), //Right
	};

	TArray<FVector> colors =
	{
		FVector(0.0f,0.0f,1.0f),//Front
		FVector(0.0f,0.0f,1.0f), //Back
		FVector(0.0f,1.0f,0.0f), //Top
		FVector(0.0f,1.0f,0.0f),//Bottom
		FVector(1.0f,0.0f,0.0f),//Left
		FVector(1.0f,0.0f,0.0f), //Right
	};

	TArray<TArray<uint32>> cubeFaces =
	{
		{0,1,2,3}, //Front
		{7,6,5,4}, //Back
		{1,5,6,2}, //Top
		{4,0,3,7}, //Bottom
		{4,5,1,0}, //Left
		{3,2,6,7}, //Right
	};

	FMeshData CubeMeshData;

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			FVertex Vertex;
			Vertex.Position = positions[cubeFaces[i][j]];
			Vertex.Color = FVector4(colors[i], 1.0f);
			CubeMeshData.Vertices.push_back(Vertex);
		}

		uint32 BaseVertexIndex = i * 4;

		CubeMeshData.Indices.push_back(BaseVertexIndex + 0);
		CubeMeshData.Indices.push_back(BaseVertexIndex + 1);
		CubeMeshData.Indices.push_back(BaseVertexIndex + 2);

		CubeMeshData.Indices.push_back(BaseVertexIndex + 0);
		CubeMeshData.Indices.push_back(BaseVertexIndex + 2);
		CubeMeshData.Indices.push_back(BaseVertexIndex + 3);
	}
	return CubeMeshData;
}

FMeshData FGeometryGenerator::CreateSphere(float Radius, uint32 NumSlices, uint32 NumStacks)
{
	FMeshData SphereMeshData;

	//const float SliceStep = FMath::PI*2 / NumSlices; // 대충 케이크 자르기 생각하면 됨. 몇조각으로 자를꺼냐? 근데 모양은 구체임 ㅋ
	//const float StackStep = FMath::PI / NumStacks; // 케이크 빵을 몇겹으로 할꺼냐? 근데 모양은 구체임 ㅋ

	//for (uint32 i = 0; i <= NumStacks; i++)
	//{
	//	FVector(0.0f - Radius, 0.0f, 0.0f)
	//	FVector StackStartPoint = Math::RotateZ(Vector3(0.0f, -_radius, 0.0f), i * stackStep);
	//	for (UInt32 j = 0; j <= _numSlices; j++)
	//	{
	//		Vertex vertex;
	//		vertex.position = Math::RotateY(StackStartPoint, j * -sectorStep);
	//		vertex.normal = vertex.position;
	//		vertex.normal = Vector3::Normalized(vertex.normal);
	//		vertex.texCoord = Vector2(Float32(i) / _numSlices, 1.0f - Float32(j) / _numStacks);

	//		SphereMeshData.vertices.push_back(vertex);
	//	}
	//}

	//for (UInt32 i = 0; i < _numStacks; i++)
	//{
	//	const int offset = (_numSlices + 1) * i; // 1줄에 numSlices보다 1개 더있음 왜냐하면 원래 있던 점을 넣어야 되기 때문에
	//	for (UInt32 j = 0; j < _numSlices; j++)
	//	{
	//		SphereMeshData.indices.push_back(offset + j);
	//		SphereMeshData.indices.push_back(offset + _numSlices + 1 + j);
	//		SphereMeshData.indices.push_back(offset + _numSlices + 1 + j + 1);

	//		SphereMeshData.indices.push_back(offset + j);
	//		SphereMeshData.indices.push_back(offset + _numSlices + 1 + j + 1);
	//		SphereMeshData.indices.push_back(offset + j + 1);
	//	}
	//}
	return SphereMeshData;
}
