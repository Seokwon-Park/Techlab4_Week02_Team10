#pragma once
#include "Vector4.h"

// Row Vector sys
struct FMatrix{
	FVector4 M[4];

public:
	FMatrix();
	FMatrix(const FVector4& InX, const FVector4& InY, const FVector4& InZ, const FVector4& InW);
	
public:
	FMatrix ApplyScale(float Scale) const;
	FVector4 GetColumn(int i) const;
	
	FVector4 GetOrigin();
	FVector4 GetScaledAxis(FVector4& X, FVector4& Y, FVector4& Z) const; 
	FMatrix GetTransposed();
	FMatrix GetTransposed() const;
	void GetUnitAxis(FVector4& X, FVector4& Y, FVector4& Z) const;
	FMatrix Inverse();
	FVector4 InverseTransformPosition(const FVector& V) const;
	void SetAxes(const FVector4* Axis0, const FVector4* Axis1, const FVector4* Axis2, const FVector4* Axis3);
	void SetAxis(int i, const FVector& Axis);
	void SetColum(int i, FVector4 Value);
	void SetIdentity();
	void SetOrigin(const FVector& NewOrigin);
	void To3x4MatrixTranspose(float* Out) const;
	FVector4 TransformFVector4(const FVector4& V) const;
	FVector4 TransformPosition(const FVector& V) const;
	FVector4 TransformVector(const FVector& V) const;
	FMatrix TransposeAdjoint();

	//GetFrustum Planes Function// 

/* Operator */

	FMatrix& operator = (const FMatrix& Other);
	FMatrix operator - ();
	FVector4 operator[] (int Index) const;
	FVector4& operator[] (int Index);
	bool operator != (const FMatrix& Other) const;
	bool operator == (const FMatrix& Other) const;
	FMatrix operator * (const FMatrix& Other) const;
	FMatrix operator * (const float& Other) const;
	FMatrix& operator *= (const FMatrix& Other);
	FMatrix& operator *= (float Other);
	FMatrix operator + (const FMatrix& Other) const;
	FMatrix& operator += (const FMatrix& Other);
	FMatrix operator - (const FMatrix& Other) const;
	FMatrix& operator -= (const FMatrix& Other);


};

