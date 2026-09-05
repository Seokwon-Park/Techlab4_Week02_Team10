#include "EnginePCH.h"
#include "Matrix.h"

/* Constructor */

FMatrix::FMatrix()
{
	M[0][0] = 0; M[0][1] = 0; M[0][2] = 0; M[0][3] = 0;
	M[1][0] = 0; M[1][1] = 0; M[1][2] = 0; M[1][3] = 0;
	M[2][0] = 0; M[2][1] = 0; M[2][2] = 0; M[2][3] = 0;
	M[3][0] = 0; M[3][1] = 0; M[3][2] = 0; M[3][3] = 0;
}

FMatrix::FMatrix(const FVector4& InX, const FVector4& InY, const FVector4& InZ, const FVector4& InW)
{
	M[0][0] = InX.X; M[0][1] = InX.Y; M[0][2] = InX.Z; M[0][3] = InX.Z;
	M[1][0] = InY.X; M[1][1] = InY.Y; M[1][2] = InY.Z; M[1][3] = InY.Z;
	M[2][0] = InZ.X; M[2][1] = InZ.Y; M[2][2] = InZ.Z; M[2][3] = InZ.Z;
	M[3][0] = InW.X; M[3][1] = InW.Y; M[3][2] = InW.Z; M[3][3] = InW.Z;
}

/* Functions */

FMatrix FMatrix::ApplyScale(float Scale) const
{
	return FMatrix(
		FVector4(M[0][0] * Scale, M[0][1], M[0][2], M[0][3]),
		FVector4(M[1][0], M[1][1] * Scale, M[1][2], M[1][3]),
		FVector4(M[2][0], M[2][1], M[2][2] * Scale, M[2][3]),
		FVector4(M[3][0], M[3][1], M[3][2], M[3][3] * Scale)
	);
}

FVector4 FMatrix::GetOrigin()
{
	return FVector4(M[3][0], M[3][1], M[3][2], M[3][3]);
}

FMatrix FMatrix::GetTransposed() const
{
	FMatrix Result;
	Result.M[0][0] = M[0][0]; Result.M[0][1] = M[1][0]; Result.M[0][2] = M[2][0]; Result.M[0][3] = M[3][0];
	Result.M[1][0] = M[0][1]; Result.M[1][1] = M[1][1]; Result.M[1][2] = M[2][1]; Result.M[1][3] = M[3][1];
	Result.M[2][0] = M[0][2]; Result.M[2][1] = M[1][2]; Result.M[2][2] = M[2][2]; Result.M[2][3] = M[3][2];
	Result.M[3][0] = M[0][3]; Result.M[3][1] = M[1][3]; Result.M[3][2] = M[2][3]; Result.M[3][3] = M[3][3];

	return Result;
}

float FMatrix::Determinant() const
{
	float SubFactor00 = M[1][1] * (M[2][2] * M[3][3] - M[2][3] * M[3][2])
		- M[1][2] * (M[2][1] * M[3][3] - M[2][3] * M[3][1])
		+ M[1][3] * (M[2][1] * M[3][2] - M[2][2] * M[3][1]);

	float SubFactor01 = M[1][0] * (M[2][2] * M[3][3] - M[2][3] * M[3][2])
		- M[1][2] * (M[2][0] * M[3][3] - M[2][3] * M[3][0])
		+ M[1][3] * (M[2][0] * M[3][2] - M[2][2] * M[3][0]);

	float SubFactor02 = M[1][0] * (M[2][1] * M[3][3] - M[2][3] * M[3][1])
		- M[1][1] * (M[2][0] * M[3][3] - M[2][3] * M[3][0])
		+ M[1][3] * (M[2][0] * M[3][1] - M[2][1] * M[3][0]);

	float SubFactor03 = M[1][0] * (M[2][1] * M[3][2] - M[2][2] * M[3][1])
		- M[1][1] * (M[2][0] * M[3][2] - M[2][2] * M[3][0])
		+ M[1][2] * (M[2][0] * M[3][1] - M[2][1] * M[3][0]);

	return (M[0][0] * SubFactor00) - (M[0][1] * SubFactor01) + (M[0][2] * SubFactor02) - (M[0][3] * SubFactor03);
}

FMatrix FMatrix::Inverse() const
{
	const float Det = Determinant();

	if (FMath::IsNearlyZero(Det))
	{
		return Identity;
	}

	const float InvDet = 1.0f / Det;
	FMatrix Result;

	// Row 0
	Result.M[0][0] = (M[1][1] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) - M[1][2] * (M[2][1] * M[3][3] - M[2][3] * M[3][1]) + M[1][3] * (M[2][1] * M[3][2] - M[2][2] * M[3][1])) * InvDet;
	Result.M[0][1] = -(M[0][1] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) - M[0][2] * (M[2][1] * M[3][3] - M[2][3] * M[3][1]) + M[0][3] * (M[2][1] * M[3][2] - M[2][2] * M[3][1])) * InvDet;
	Result.M[0][2] = (M[0][1] * (M[1][2] * M[3][3] - M[1][3] * M[3][2]) - M[0][2] * (M[1][1] * M[3][3] - M[1][3] * M[3][1]) + M[0][3] * (M[1][1] * M[3][2] - M[1][2] * M[3][1])) * InvDet;
	Result.M[0][3] = -(M[0][1] * (M[1][2] * M[2][3] - M[1][3] * M[2][2]) - M[0][2] * (M[1][1] * M[2][3] - M[1][3] * M[2][1]) + M[0][3] * (M[1][1] * M[2][2] - M[1][2] * M[2][1])) * InvDet;

	// Row 1
	Result.M[1][0] = -(M[1][0] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) - M[1][2] * (M[2][0] * M[3][3] - M[2][3] * M[3][0]) + M[1][3] * (M[2][0] * M[3][2] - M[2][2] * M[3][0])) * InvDet;
	Result.M[1][1] = (M[0][0] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) - M[0][2] * (M[2][0] * M[3][3] - M[2][3] * M[3][0]) + M[0][3] * (M[2][0] * M[3][2] - M[2][2] * M[3][0])) * InvDet;
	Result.M[1][2] = -(M[0][0] * (M[1][2] * M[3][3] - M[1][3] * M[3][2]) - M[0][2] * (M[1][0] * M[3][3] - M[1][3] * M[3][0]) + M[0][3] * (M[1][0] * M[3][2] - M[1][2] * M[3][0])) * InvDet;
	Result.M[1][3] = (M[0][0] * (M[1][2] * M[2][3] - M[1][3] * M[2][2]) - M[0][2] * (M[1][0] * M[2][3] - M[1][3] * M[2][0]) + M[0][3] * (M[1][0] * M[2][2] - M[1][2] * M[2][0])) * InvDet;

	// Row 2
	Result.M[2][0] = (M[1][0] * (M[2][1] * M[3][3] - M[2][3] * M[3][1]) - M[1][1] * (M[2][0] * M[3][3] - M[2][3] * M[3][0]) + M[1][3] * (M[2][0] * M[3][1] - M[2][1] * M[3][0])) * InvDet;
	Result.M[2][1] = -(M[0][0] * (M[2][1] * M[3][3] - M[2][3] * M[3][1]) - M[0][1] * (M[2][0] * M[3][3] - M[2][3] * M[3][0]) + M[0][3] * (M[2][0] * M[3][1] - M[2][1] * M[3][0])) * InvDet;
	Result.M[2][2] = (M[0][0] * (M[1][1] * M[3][3] - M[1][3] * M[3][1]) - M[0][1] * (M[1][0] * M[3][3] - M[1][3] * M[3][0]) + M[0][3] * (M[1][0] * M[3][1] - M[1][1] * M[3][0])) * InvDet;
	Result.M[2][3] = -(M[0][0] * (M[1][1] * M[2][3] - M[1][3] * M[2][1]) - M[0][1] * (M[1][0] * M[2][3] - M[1][3] * M[2][0]) + M[0][3] * (M[1][0] * M[2][1] - M[1][1] * M[2][0])) * InvDet;

	// Row 3
	Result.M[3][0] = -(M[1][0] * (M[2][1] * M[3][2] - M[2][2] * M[3][1]) - M[1][1] * (M[2][0] * M[3][2] - M[2][2] * M[3][0]) + M[1][2] * (M[2][0] * M[3][1] - M[2][1] * M[3][0])) * InvDet;
	Result.M[3][1] = (M[0][0] * (M[2][1] * M[3][2] - M[2][2] * M[3][1]) - M[0][1] * (M[2][0] * M[3][2] - M[2][2] * M[3][0]) + M[0][2] * (M[2][0] * M[3][1] - M[2][1] * M[3][0])) * InvDet;
	Result.M[3][2] = -(M[0][0] * (M[1][1] * M[3][2] - M[1][2] * M[3][1]) - M[0][1] * (M[1][0] * M[3][2] - M[1][2] * M[3][0]) + M[0][2] * (M[1][0] * M[3][1] - M[1][1] * M[3][0])) * InvDet;
	Result.M[3][3] = (M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]) - M[0][1] * (M[1][0] * M[2][2] - M[1][2] * M[2][0]) + M[0][2] * (M[1][0] * M[2][1] - M[1][1] * M[2][0])) * InvDet;

	return Result;
}

FVector4 FMatrix::InverseTransformPosition(const FVector& V) const
{
	FMatrix InvMatrix = Inverse();
	return InvMatrix.TransformPosition(V);
}

FVector4 FMatrix::GetColumn(int i) const
{
	return FVector4(M[0][i], M[1][i], M[2][i], M[3][i]);
}

void FMatrix::SetColumn(int i, FVector4 Value)
{
	M[0][i] = Value[0];
	M[1][i] = Value[1];
	M[2][i] = Value[2];
	M[3][i] = Value[3];
}

void FMatrix::SetIdentity()
{
	M[0][0] = 1; M[0][1] = 0; M[0][2] = 0; M[0][3] = 0;
	M[1][0] = 0; M[1][1] = 1; M[1][2] = 0; M[1][3] = 0;
	M[2][0] = 0; M[2][1] = 0; M[2][2] = 1; M[2][3] = 0;
	M[3][0] = 0; M[3][1] = 0; M[3][2] = 0; M[3][3] = 1;
}

void FMatrix::SetOrigin(const FVector & NewOrigin)
{
	M[3][0] = NewOrigin.X;
	M[3][1] = NewOrigin.Y;
	M[3][2] = NewOrigin.Z;
}

FVector4 FMatrix::TransformFVector4(const FVector4& V) const
{
	return FVector4(
		V.X * M[0][0] + V.Y * M[1][0] + V.Z * M[2][0] + V.W * M[3][0],
		V.X * M[0][1] + V.Y * M[1][1] + V.Z * M[2][1] + V.W * M[3][1],
		V.X * M[0][2] + V.Y * M[1][2] + V.Z * M[2][2] + V.W * M[3][2],
		V.X * M[0][3] + V.Y * M[1][3] + V.Z * M[2][3] + V.W * M[3][3]
	);
}

FVector4 FMatrix::TransformPosition(const FVector& V) const
{
	return TransformFVector4(FVector4(V.X, V.Y, V.Z, 1.0f));
}

FVector4 FMatrix::TransformVector(const FVector& V) const
{
	return TransformFVector4(FVector4(V.X, V.Y, V.Z, 0.0f));
}

/* Operator */

FMatrix& FMatrix::operator = (const FMatrix& Other)
{
	M[0][0] = Other[0][0]; M[0][1] = Other[0][1]; M[0][2] = Other[0][2]; M[0][3] = Other[0][3];
	M[1][0] = Other[1][0]; M[1][1] = Other[1][1]; M[1][2] = Other[1][2]; M[1][3] = Other[1][3];
	M[2][0] = Other[2][0]; M[2][1] = Other[2][1]; M[2][2] = Other[2][2]; M[2][3] = Other[2][3];
	M[3][0] = Other[3][0]; M[3][1] = Other[3][1]; M[3][2] = Other[3][2]; M[3][3] = Other[3][3];

	return *this;
}

FMatrix FMatrix::operator - () 
{
	return FMatrix(
		-FVector4(M[0][0], M[0][1], M[0][2], M[0][3]),
		-FVector4(M[1][0], M[1][1], M[1][2], M[1][3]),
		-FVector4(M[2][0], M[2][1], M[2][2], M[2][3]),
		-FVector4(M[3][0], M[3][1], M[3][2], M[3][3])
	);
}

const float* FMatrix::operator[] (int Index) const
{
	return M[Index];
}

float* FMatrix::operator[] (int Index)
{
	return M[Index];
}

bool FMatrix::operator != (const FMatrix& Other) const
{
	if (M[0] == Other[0] || M[1] == Other[1] || M[2] == Other[2] || M[3] == Other[3])
		return false;
	else
		return true;
}

bool FMatrix::operator == (const FMatrix& Other) const 
{
	if (M[0] != Other[0] || M[1] != Other[1] || M[2] != Other[2] || M[3] != Other[3])
		return false;
	else
		return true;
}

FMatrix FMatrix::operator * (const FMatrix& Other) const
{
	// Other의 전치 행렬 반환
	FMatrix RM;
	FMatrix TM = Other.GetTransposed();

	// Row 0
	RM.M[0][0] = M[0][0] * TM.M[0][0] + M[0][1] * TM.M[0][1] + M[0][2] * TM.M[0][2] + M[0][3] * TM.M[0][3];
	RM.M[0][1] = M[0][0] * TM.M[1][0] + M[0][1] * TM.M[1][1] + M[0][2] * TM.M[1][2] + M[0][3] * TM.M[1][3];
	RM.M[0][2] = M[0][0] * TM.M[2][0] + M[0][1] * TM.M[2][1] + M[0][2] * TM.M[2][2] + M[0][3] * TM.M[2][3];
	RM.M[0][3] = M[0][0] * TM.M[3][0] + M[0][1] * TM.M[3][1] + M[0][2] * TM.M[3][2] + M[0][3] * TM.M[3][3];

	// Row 1
	RM.M[1][0] = M[1][0] * TM.M[0][0] + M[1][1] * TM.M[0][1] + M[1][2] * TM.M[0][2] + M[1][3] * TM.M[0][3];
	RM.M[1][1] = M[1][0] * TM.M[1][0] + M[1][1] * TM.M[1][1] + M[1][2] * TM.M[1][2] + M[1][3] * TM.M[1][3];
	RM.M[1][2] = M[1][0] * TM.M[2][0] + M[1][1] * TM.M[2][1] + M[1][2] * TM.M[2][2] + M[1][3] * TM.M[2][3];
	RM.M[1][3] = M[1][0] * TM.M[3][0] + M[1][1] * TM.M[3][1] + M[1][2] * TM.M[3][2] + M[1][3] * TM.M[3][3];

	// Row 2
	RM.M[2][0] = M[2][0] * TM.M[0][0] + M[2][1] * TM.M[0][1] + M[2][2] * TM.M[0][2] + M[2][3] * TM.M[0][3];
	RM.M[2][1] = M[2][0] * TM.M[1][0] + M[2][1] * TM.M[1][1] + M[2][2] * TM.M[1][2] + M[2][3] * TM.M[1][3];
	RM.M[2][2] = M[2][0] * TM.M[2][0] + M[2][1] * TM.M[2][1] + M[2][2] * TM.M[2][2] + M[2][3] * TM.M[2][3];
	RM.M[2][3] = M[2][0] * TM.M[3][0] + M[2][1] * TM.M[3][1] + M[2][2] * TM.M[3][2] + M[2][3] * TM.M[3][3];

	// Row 3
	RM.M[3][0] = M[3][0] * TM.M[0][0] + M[3][1] * TM.M[0][1] + M[3][2] * TM.M[0][2] + M[3][3] * TM.M[0][3];
	RM.M[3][1] = M[3][0] * TM.M[1][0] + M[3][1] * TM.M[1][1] + M[3][2] * TM.M[1][2] + M[3][3] * TM.M[1][3];
	RM.M[3][2] = M[3][0] * TM.M[2][0] + M[3][1] * TM.M[2][1] + M[3][2] * TM.M[2][2] + M[3][3] * TM.M[2][3];
	RM.M[3][3] = M[3][0] * TM.M[3][0] + M[3][1] * TM.M[3][1] + M[3][2] * TM.M[3][2] + M[3][3] * TM.M[3][3];

	return RM;
}

FMatrix FMatrix::operator * (const float& Other) const 
{
	return FMatrix(
		FVector4(M[0][0] * Other, M[0][1] * Other, M[0][2] * Other, M[0][3] * Other),
		FVector4(M[1][0] * Other, M[1][1] * Other, M[1][2] * Other, M[1][3] * Other),
		FVector4(M[2][0] * Other, M[2][1] * Other, M[2][2] * Other, M[2][3] * Other),
		FVector4(M[3][0] * Other, M[3][1] * Other, M[3][2] * Other, M[3][3] * Other)
	);
}

FMatrix& FMatrix::operator *= (const FMatrix& Other)
{
	FMatrix RM;
	FMatrix TM = Other.GetTransposed();

	// Row 0
	RM.M[0][0] = M[0][0] * TM.M[0][0] + M[0][1] * TM.M[0][1] + M[0][2] * TM.M[0][2] + M[0][3] * TM.M[0][3];
	RM.M[0][1] = M[0][0] * TM.M[1][0] + M[0][1] * TM.M[1][1] + M[0][2] * TM.M[1][2] + M[0][3] * TM.M[1][3];
	RM.M[0][2] = M[0][0] * TM.M[2][0] + M[0][1] * TM.M[2][1] + M[0][2] * TM.M[2][2] + M[0][3] * TM.M[2][3];
	RM.M[0][3] = M[0][0] * TM.M[3][0] + M[0][1] * TM.M[3][1] + M[0][2] * TM.M[3][2] + M[0][3] * TM.M[3][3];

	// Row 1
	RM.M[1][0] = M[1][0] * TM.M[0][0] + M[1][1] * TM.M[0][1] + M[1][2] * TM.M[0][2] + M[1][3] * TM.M[0][3];
	RM.M[1][1] = M[1][0] * TM.M[1][0] + M[1][1] * TM.M[1][1] + M[1][2] * TM.M[1][2] + M[1][3] * TM.M[1][3];
	RM.M[1][2] = M[1][0] * TM.M[2][0] + M[1][1] * TM.M[2][1] + M[1][2] * TM.M[2][2] + M[1][3] * TM.M[2][3];
	RM.M[1][3] = M[1][0] * TM.M[3][0] + M[1][1] * TM.M[3][1] + M[1][2] * TM.M[3][2] + M[1][3] * TM.M[3][3];

	// Row 2
	RM.M[2][0] = M[2][0] * TM.M[0][0] + M[2][1] * TM.M[0][1] + M[2][2] * TM.M[0][2] + M[2][3] * TM.M[0][3];
	RM.M[2][1] = M[2][0] * TM.M[1][0] + M[2][1] * TM.M[1][1] + M[2][2] * TM.M[1][2] + M[2][3] * TM.M[1][3];
	RM.M[2][2] = M[2][0] * TM.M[2][0] + M[2][1] * TM.M[2][1] + M[2][2] * TM.M[2][2] + M[2][3] * TM.M[2][3];
	RM.M[2][3] = M[2][0] * TM.M[3][0] + M[2][1] * TM.M[3][1] + M[2][2] * TM.M[3][2] + M[2][3] * TM.M[3][3];

	// Row 3
	RM.M[3][0] = M[3][0] * TM.M[0][0] + M[3][1] * TM.M[0][1] + M[3][2] * TM.M[0][2] + M[3][3] * TM.M[0][3];
	RM.M[3][1] = M[3][0] * TM.M[1][0] + M[3][1] * TM.M[1][1] + M[3][2] * TM.M[1][2] + M[3][3] * TM.M[1][3];
	RM.M[3][2] = M[3][0] * TM.M[2][0] + M[3][1] * TM.M[2][1] + M[3][2] * TM.M[2][2] + M[3][3] * TM.M[2][3];
	RM.M[3][3] = M[3][0] * TM.M[3][0] + M[3][1] * TM.M[3][1] + M[3][2] * TM.M[3][2] + M[3][3] * TM.M[3][3];

	*this = RM;
	return *this;
}

FMatrix& FMatrix::operator *= (float Other) 
{
	M[0][0] *= Other; M[0][1] *= Other; M[0][2] *= Other; M[0][3] *= Other;
	M[1][0] *= Other; M[1][1] *= Other; M[1][2] *= Other; M[1][3] *= Other;
	M[2][0] *= Other; M[2][1] *= Other; M[2][2] *= Other; M[2][3] *= Other;
	M[3][0] *= Other; M[3][1] *= Other; M[3][2] *= Other; M[3][3] *= Other;

	return *this;
} 

FMatrix FMatrix::operator + (const FMatrix& Other) const
{
	FMatrix Result;
	Result.M[0][0] = M[0][0] + Other[0][0];
	Result.M[0][1] = M[0][1] + Other[0][1]; 
	Result.M[0][2] = M[0][2] + Other[0][2]; 
	Result.M[0][3] = M[0][3] + Other[0][3];

	Result.M[1][0] = M[1][0] + Other[1][0];
	Result.M[1][1] = M[1][1] + Other[1][1];
	Result.M[1][2] = M[1][2] + Other[1][2];
	Result.M[1][3] = M[1][3] + Other[1][3];

	Result.M[2][0] = M[2][0] + Other[2][0];
	Result.M[2][1] = M[2][1] + Other[2][1];
	Result.M[2][2] = M[2][2] + Other[2][2];
	Result.M[2][3] = M[2][3] + Other[2][3];

	Result.M[3][0] = M[3][0] + Other[3][0];
	Result.M[3][1] = M[3][1] + Other[3][1];
	Result.M[3][2] = M[3][2] + Other[3][2];
	Result.M[3][3] = M[3][3] + Other[3][3];

	return Result;
}

FMatrix& FMatrix::operator += (const FMatrix& Other)
{
	M[0][0] = M[0][0] + Other[0][0];
	M[0][1] = M[0][1] + Other[0][1];
	M[0][2] = M[0][2] + Other[0][2];
	M[0][3] = M[0][3] + Other[0][3];

	M[1][0] = M[1][0] + Other[1][0];
	M[1][1] = M[1][1] + Other[1][1];
	M[1][2] = M[1][2] + Other[1][2];
	M[1][3] = M[1][3] + Other[1][3];

	M[2][0] = M[2][0] + Other[2][0];
	M[2][1] = M[2][1] + Other[2][1];
	M[2][2] = M[2][2] + Other[2][2];
	M[2][3] = M[2][3] + Other[2][3];

	M[3][0] = M[3][0] + Other[3][0];
	M[3][1] = M[3][1] + Other[3][1];
	M[3][2] = M[3][2] + Other[3][2];
	M[3][3] = M[3][3] + Other[3][3];

	return *this;
}

FMatrix FMatrix::operator - (const FMatrix& Other) const
{
	FMatrix Result;
	Result.M[0][0] = M[0][0] + Other[0][0];
	Result.M[0][1] = M[0][1] + Other[0][1];
	Result.M[0][2] = M[0][2] + Other[0][2];
	Result.M[0][3] = M[0][3] + Other[0][3];

	Result.M[1][0] = M[1][0] + Other[1][0];
	Result.M[1][1] = M[1][1] + Other[1][1];
	Result.M[1][2] = M[1][2] + Other[1][2];
	Result.M[1][3] = M[1][3] + Other[1][3];

	Result.M[2][0] = M[2][0] + Other[2][0];
	Result.M[2][1] = M[2][1] + Other[2][1];
	Result.M[2][2] = M[2][2] + Other[2][2];
	Result.M[2][3] = M[2][3] + Other[2][3];

	Result.M[3][0] = M[3][0] + Other[3][0];
	Result.M[3][1] = M[3][1] + Other[3][1];
	Result.M[3][2] = M[3][2] + Other[3][2];
	Result.M[3][3] = M[3][3] + Other[3][3];

	return Result;
}

FMatrix& FMatrix::operator -= (const FMatrix& Other)
{
	M[0][0] = M[0][0] - Other[0][0];
	M[0][1] = M[0][1] - Other[0][1];
	M[0][2] = M[0][2] - Other[0][2];
	M[0][3] = M[0][3] - Other[0][3];

	M[1][0] = M[1][0] - Other[1][0];
	M[1][1] = M[1][1] - Other[1][1];
	M[1][2] = M[1][2] - Other[1][2];
	M[1][3] = M[1][3] - Other[1][3];

	M[2][0] = M[2][0] - Other[2][0];
	M[2][1] = M[2][1] - Other[2][1];
	M[2][2] = M[2][2] - Other[2][2];
	M[2][3] = M[2][3] - Other[2][3];

	M[3][0] = M[3][0] - Other[3][0];
	M[3][1] = M[3][1] - Other[3][1];
	M[3][2] = M[3][2] - Other[3][2];
	M[3][3] = M[3][3] - Other[3][3];

	return *this;
}