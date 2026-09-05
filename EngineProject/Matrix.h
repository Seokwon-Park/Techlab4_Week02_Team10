#pragma once

#include "EngineMath.h"
#include <DirectXMath.h>

using namespace DirectX;

struct FVector;
struct FVector4;

// Row Vector sys
struct FMatrix{
	float M[4][4];

public:
	FMatrix();
	FMatrix(const FVector4& InX, const FVector4& InY, const FVector4& InZ, const FVector4& InW);
	FMatrix(
		const float& f00, const float& f01, const float& f02, const float& f03,
		const float& f10, const float& f11, const float& f12, const float& f13,
		const float& f20, const float& f21, const float& f22, const float& f23,
		const float& f30, const float& f31, const float& f32, const float& f33
	);

public:
	void SetAxes(const FVector4& Axis0, const FVector4& Axis1, const FVector4& Axis2, const FVector4& Axis3);
	void SetAxis(int i, const FVector& Axis);
	void GetUnitAxis(FVector4& X, FVector4& Y, FVector4& Z) const;

	XMMATRIX FMatrixToXMMatrix() const;

	FVector4 GetColumn(int i) const;
	FVector4 GetOrigin();
	FVector4 GetScaledAxis(FVector4& X, FVector4& Y, FVector4& Z) const; 
	FVector4 TransformFVector4(const FVector4& V) const;
	FVector4 TransformPosition(const FVector& V) const;
	FVector4 TransformVector(const FVector& V) const;
	FVector4 InverseTransformPosition(const FVector& V) const;

	FMatrix ApplyScale(float Scale) const;
	FMatrix GetTransposed() const;
	FMatrix Inverse() const;
	
	FMatrix Multiply(const FMatrix& Other);
	
	float Determinant() const;
	
	void SetColumn(int i, FVector4 Value);
	void SetIdentity();
	void SetOrigin(const FVector& NewOrigin);

	// 
	//void To3x4MatrixTranspose(float* Out) const;
	// FMatrix TransposeAdjoint();

	//GetFrustum Planes Function// 

	/* Statics */

	static XMMATRIX FMatrixToXMMatrix(const FMatrix& M);
	static FMatrix XMMatrixToFMatrix(const XMMATRIX& Matrix);

	// 월드 공간 행렬 생성 함수
	static FMatrix MakeWorld(const FVector& Scale, const FVector& Rotation, const FVector& Translation);
	// 뷰행렬 생성 함수
	static FMatrix MakeView(const FVector& Eye, const FVector& Target, const FVector& Up);
	// 투영행렬 생성 함수
	static FMatrix MakePerspective(float FovY, float AspectRatio, float NearX, float FarX);
	static FMatrix MakeOrthographic(float ViewWidth, float ViewHeight, float NearZ, float FarZ);


/* Operator */

	FMatrix& operator = (const FMatrix& Other);
	FMatrix operator - ();

	const float* operator[] (int Index) const;
	float* operator[] (int Index);

	bool operator != (const FMatrix& Other) const;
	bool operator == (const FMatrix& Other) const;

	FMatrix operator * (const FMatrix& Other) const;
	FMatrix operator * (const float& Other) const;
	FVector4 operator * (const FVector4& Other) const;

	FMatrix& operator *= (const FMatrix& Other);
	FMatrix& operator *= (float Other);

	FMatrix operator + (const FMatrix& Other) const;
	FMatrix& operator += (const FMatrix& Other);
	FMatrix operator - (const FMatrix& Other) const;
	FMatrix& operator -= (const FMatrix& Other);


};

/* Constants */

/* Global Operator*/
std::ostream& operator << (std::ostream& OS, const FMatrix& M);
