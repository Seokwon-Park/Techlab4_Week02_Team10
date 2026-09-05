#include "EnginePCH.h"

#include "Matrix.h"
#include "Vector.h"
#include "Vector4.h"

/* Constants */
inline static const FMatrix Identity
= FMatrix(FVector4(1, 0, 0, 0), FVector4(0, 1, 0, 0), FVector4(0, 0, 1, 0), FVector4(0, 0, 0, 1));

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
	M[0][0] = InX.X; M[0][1] = InX.Y; M[0][2] = InX.Z; M[0][3] = InX.W;
	M[1][0] = InY.X; M[1][1] = InY.Y; M[1][2] = InY.Z; M[1][3] = InY.W;
	M[2][0] = InZ.X; M[2][1] = InZ.Y; M[2][2] = InZ.Z; M[2][3] = InZ.W;
	M[3][0] = InW.X; M[3][1] = InW.Y; M[3][2] = InW.Z; M[3][3] = InW.W;
}

FMatrix::FMatrix(
	const float& f00, const float& f01, const float& f02, const float& f03,
	const float& f10, const float& f11, const float& f12, const float& f13,
	const float& f20, const float& f21, const float& f22, const float& f23,
	const float& f30, const float& f31, const float& f32, const float& f33
)
{
	M[0][0] = f00; M[0][1] = f01; M[0][2] = f02; M[0][3] = f03;
	M[1][0] = f10; M[1][1] = f11; M[1][2] = f11; M[1][3] = f13;
	M[2][0] = f20; M[2][1] = f21; M[2][2] = f22; M[2][3] = f23;
	M[3][0] = f30; M[3][1] = f31; M[3][2] = f32; M[3][3] = f33;
}

/* Functions */

XMMATRIX FMatrix::FMatrixToXMMatrix() const
{
	return XMMATRIX(
		M[0][0], M[0][1], M[0][2], M[0][3],
		M[1][0], M[1][1], M[1][2], M[1][3],
		M[2][0], M[2][1], M[2][2], M[2][3],
		M[3][0], M[3][1], M[3][2], M[3][3]
	);
}

FMatrix FMatrix::XMMatrixToFMatrix(const XMMATRIX& Matrix) const
{
	FMatrix Result;

	DirectX::XMFLOAT4X4 Temp;
	DirectX::XMStoreFloat4x4(&Temp, Matrix);

	for (int Row = 0; Row < 4; ++Row)
	{
		for (int Col = 0; Col < 4; ++Col)
		{
			Result.M[Row][Col] = Temp.m[Row][Col];
		}
	}

	return Result;
}


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
	return XMMatrixToFMatrix(XMMatrixTranspose(FMatrixToXMMatrix()));
}

float FMatrix::Determinant() const
{
	return XMVectorGetX(XMMatrixDeterminant(FMatrixToXMMatrix()));
}

FMatrix FMatrix::Inverse() const
{
	return XMMatrixToFMatrix(XMMatrixInverse(&XMMatrixDeterminant(FMatrixToXMMatrix()), FMatrixToXMMatrix()));
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

void FMatrix::SetAxes(const FVector4& Axis0, const FVector4& Axis1, const FVector4& Axis2, const FVector4& Axis3)
{
	M[0][0] = Axis0.X; M[0][1] = Axis0.Y; M[0][2] = Axis0.Z; M[0][3] = Axis0.W;
	M[1][0] = Axis0.X; M[1][1] = Axis0.Y; M[1][2] = Axis0.Z; M[1][3] = Axis0.W;
	M[2][0] = Axis0.X; M[2][1] = Axis0.Y; M[2][2] = Axis0.Z; M[2][3] = Axis0.W;
	M[3][0] = Axis0.X; M[3][1] = Axis0.Y; M[3][2] = Axis0.Z; M[3][3] = Axis0.W;
}

void FMatrix::SetAxis(int i, const FVector& Axis)
{
	M[i][0] = Axis.X;
	M[i][1] = Axis.Y;
	M[i][2] = Axis.Z;
}

void FMatrix::GetUnitAxis(FVector4& X, FVector4& Y, FVector4& Z) const
{
	X = X.Normalize();
	Y = Y.Normalize();
	Z = Z.Normalize();
}

FMatrix FMatrix::MakeView(const FVector& Eye, const FVector& Target, const FVector& Up)
{
	XMVECTOR XEye = Eye.FVectorToXMVector();
	XMVECTOR XTarget = Target.FVectorToXMVector();
	XMVECTOR XUp = Up.FVectorToXMVector();

	XMMATRIX View = XMMatrixLookAtLH(XEye, XTarget, XUp);

	return XMMatrixToFMatrix(View);
}

FMatrix FMatrix::MakePerspective(float FovY, float AspectRatio, float NearZ, float FarZ)
{
	XMMATRIX Projection = XMMatrixPerspectiveFovLH(FovY, AspectRatio, NearZ, FarZ);
	return XMMatrixToFMatrix(Projection);
}

FMatrix FMatrix::MakeOrthographic(float FovY, float AspectRatio, float NearZ, float FarZ)
{
	XMMATRIX Projection = XMMatrixOrthographicLH(FovY, AspectRatio, NearZ, FarZ);
	return XMMatrixToFMatrix(Projection);
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

bool FMatrix::operator == (const FMatrix& Other) const
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (M[i][j] != Other.M[i][j]) return false;
		}
	}
	return true;
}

bool FMatrix::operator != (const FMatrix& Other) const
{
	return !(*this == Other);
}

FMatrix FMatrix::operator * (const FMatrix& Other) const
{
	XMMATRIX M1 = FMatrixToXMMatrix();
	XMMATRIX M2 = Other.FMatrixToXMMatrix();
	
	return XMMatrixToFMatrix(XMMatrixMultiply(M1, M2));
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

FVector4 FMatrix::operator * (const FVector4& Other) const
{
	return TransformFVector4(Other);
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
	Result.M[0][0] = M[0][0] - Other[0][0];
	Result.M[0][1] = M[0][1] - Other[0][1];
	Result.M[0][2] = M[0][2] - Other[0][2];
	Result.M[0][3] = M[0][3] - Other[0][3];

	Result.M[1][0] = M[1][0] - Other[1][0];
	Result.M[1][1] = M[1][1] - Other[1][1];
	Result.M[1][2] = M[1][2] - Other[1][2];
	Result.M[1][3] = M[1][3] - Other[1][3];

	Result.M[2][0] = M[2][0] - Other[2][0];
	Result.M[2][1] = M[2][1] - Other[2][1];
	Result.M[2][2] = M[2][2] - Other[2][2];
	Result.M[2][3] = M[2][3] - Other[2][3];

	Result.M[3][0] = M[3][0] - Other[3][0];
	Result.M[3][1] = M[3][1] - Other[3][1];
	Result.M[3][2] = M[3][2] - Other[3][2];
	Result.M[3][3] = M[3][3] - Other[3][3];

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



/* Global Operator */
std::ostream& operator << (std::ostream& OS, const FMatrix& M )
{
	OS << M[0][0] << " " << M[0][1] << " " << M[0][2] << " " << M[0][3] << "\n";
	OS << M[1][0] << " " << M[1][1] << " " << M[1][2] << " " << M[1][3] << "\n";
	OS << M[2][0] << " " << M[2][1] << " " << M[2][2] << " " << M[2][3] << "\n";
	OS << M[3][0] << " " << M[3][1] << " " << M[3][2] << " " << M[3][3] << "\n";
	return OS;
}