#include "EnginePCH.h"
#include "Matrix.h"

/* Constructor */

FMatrix::FMatrix()
{
	FVector V;
	M[0] = V;
	M[1] = V;
	M[2] = V;
	M[3] = V;
}

FMatrix::FMatrix(const FVector4& InX, const FVector4& InY, const FVector4& InZ, const FVector4& InW)
{
	M[0] = InX;
	M[1] = InY;
	M[2] = InZ;
	M[3] = InW;
}

/* Functions */

FVector4 FMatrix::GetOrigin()
{
	return M[3];
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

void FMatrix::SetIdentity()
{
	M[0] = FVector4(XAxisVector);
	M[1] = FVector4(YAxisVector);
	M[2] = FVector4(ZAxisVector);
	M[3] = FVector4(ZeroVector, 1);
}

void FMatrix::SetOrigin(const FVector & NewOrigin)
{
	M[3] = FVector4(NewOrigin, 1.0f);
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
	M[0] = Other[0];
	M[1] = Other[1];
	M[2] = Other[2];
	M[3] = Other[3];

	return *this;
}

FMatrix FMatrix::operator - () 
{
	return FMatrix(-M[0], -M[1], -M[2], -M[3]);
}

FVector4 FMatrix::operator[] (int Index) const
{
	return M[Index];
}

FVector4& FMatrix::operator[] (int Index)
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

	RM[0][0] = FVector4::DotProduct(M[0], TM[0]); 
	RM[0][1] = FVector4::DotProduct(M[0], TM[1]); 
	RM[0][2] = FVector4::DotProduct(M[0], TM[2]); 
	RM[0][3] = FVector4::DotProduct(M[0], TM[3]);
	
	RM[1][0] = FVector4::DotProduct(M[1], TM[0]); 
	RM[1][1] = FVector4::DotProduct(M[1], TM[1]); 
	RM[1][2] = FVector4::DotProduct(M[1], TM[2]); 
	RM[1][3] = FVector4::DotProduct(M[1], TM[3]);
	
	RM[2][0] = FVector4::DotProduct(M[2], TM[0]); 
	RM[2][1] = FVector4::DotProduct(M[2], TM[1]); 
	RM[2][2] = FVector4::DotProduct(M[2], TM[2]); 
	RM[2][3] = FVector4::DotProduct(M[2], TM[3]);
	
	RM[3][0] = FVector4::DotProduct(M[3], TM[0]); 
	RM[3][1] = FVector4::DotProduct(M[3], TM[1]); 
	RM[3][2] = FVector4::DotProduct(M[3], TM[2]); 
	RM[3][3] = FVector4::DotProduct(M[3], TM[3]);

	return RM;
}

FMatrix FMatrix::operator * (const float& Other) const 
{
	return FMatrix(M[0] * Other, M[1] * Other, M[2] * Other, M[3] * Other);
}

FMatrix& FMatrix::operator *= (const FMatrix& Other)
{
	FMatrix RM;
	FMatrix TM = Other.GetTransposed();

	RM[0][0] = FVector4::DotProduct(M[0], TM[0]);
	RM[0][1] = FVector4::DotProduct(M[0], TM[1]);
	RM[0][2] = FVector4::DotProduct(M[0], TM[2]);
	RM[0][3] = FVector4::DotProduct(M[0], TM[3]);

	RM[1][0] = FVector4::DotProduct(M[1], TM[0]);
	RM[1][1] = FVector4::DotProduct(M[1], TM[1]);
	RM[1][2] = FVector4::DotProduct(M[1], TM[2]);
	RM[1][3] = FVector4::DotProduct(M[1], TM[3]);

	RM[2][0] = FVector4::DotProduct(M[2], TM[0]);
	RM[2][1] = FVector4::DotProduct(M[2], TM[1]);
	RM[2][2] = FVector4::DotProduct(M[2], TM[2]);
	RM[2][3] = FVector4::DotProduct(M[2], TM[3]);

	RM[3][0] = FVector4::DotProduct(M[3], TM[0]);
	RM[3][1] = FVector4::DotProduct(M[3], TM[1]);
	RM[3][2] = FVector4::DotProduct(M[3], TM[2]);
	RM[3][3] = FVector4::DotProduct(M[3], TM[3]);

	M[0][0] = RM[0][0]; M[0][1] = RM[0][1]; M[0][2] = RM[0][2]; M[0][3] = RM[0][3];
	M[1][0] = RM[1][0]; M[1][1] = RM[1][1]; M[1][2] = RM[1][2]; M[1][3] = RM[1][3];
	M[2][0] = RM[2][0]; M[2][1] = RM[2][1]; M[2][2] = RM[2][2]; M[2][3] = RM[2][3];
	M[3][0] = RM[3][0]; M[3][1] = RM[3][1]; M[3][2] = RM[3][2]; M[3][3] = RM[3][3];
	return *this;
}

FMatrix& FMatrix::operator *= (float Other) 
{
	M[0] = M[0] * Other;
	M[1] = M[1] * Other;
	M[2] = M[2] * Other;
	M[3] = M[3] * Other;

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