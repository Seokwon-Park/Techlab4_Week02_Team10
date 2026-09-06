#include "EnginePCH.h"
#include "MatrixRegister.h"

using namespace VectorSIMD;

FMatrixRegister::FMatrixRegister()
{
	R[0] = VectorSIMD::SetZero();
	R[1] = VectorSIMD::SetZero();
	R[2] = VectorSIMD::SetZero();
	R[3] = VectorSIMD::SetZero();
}

FMatrixRegister::FMatrixRegister(FVectorRegister R0, FVectorRegister R1, FVectorRegister R2, FVectorRegister R3)
{
	R[0] = R0;
	R[1] = R1;
	R[2] = R2;
	R[3] = R3;
}

FMatrixRegister FMatrixRegister::Transpose() const
{
	FMatrixRegister Result = *this;
	VectorSIMD::Transpose(Result.R[0], Result.R[1], Result.R[2], Result.R[3]);
	return Result;
}

float FMatrixRegister::Determinant3x3(FVectorRegister A, FVectorRegister B, FVectorRegister C) const
{
	FVectorRegister Cross = VectorSIMD::Cross3(B, C);
	return VectorSIMD::Dot(A, Cross);
}

inline float FMatrixRegister::Determinant() const
{
	const FVectorRegister& A = R[0];
	const FVectorRegister& B = R[1];
	const FVectorRegister& C = R[2];
	const FVectorRegister& D = R[3];

	// C00 = +(fgh / jkl / nop)
	FVectorRegister M00 = Swizzle<1, 2, 3, 3>(B);
	FVectorRegister M01 = Swizzle<1, 2, 3, 3>(C);
	FVectorRegister M02 = Swizzle<1, 2, 3, 3>(D);

	float C00 = Determinant3x3(M00, M01, M02);

	// C01 = -(egh / ikl / mop)
	FVectorRegister M10 = Shuffle<0, 2, 3, 3>(B, B);
	FVectorRegister M11 = Shuffle<0, 2, 3, 3>(C, C);
	FVectorRegister M12 = Shuffle<0, 2, 3, 3>(D, D);

	float C01 = -Determinant3x3(M10, M11, M12);

	// C02 = +(efh / ijl / mnp)
	FVectorRegister M20 = Shuffle<0, 1, 3, 3>(B, B);
	FVectorRegister M21 = Shuffle<0, 1, 3, 3>(C, C);
	FVectorRegister M22 = Shuffle<0, 1, 3, 3>(D, D);

	float C02 = Determinant3x3(M20, M21, M22);

	// C03 = -(efg / ijk / mno)
	float C03 = -Determinant3x3(B, C, D);

	// determinant
	return VectorSIMD::Dot(A, VectorSIMD::SetVal(C00, C01, C02, C03));
}


FMatrixRegister FMatrixRegister::Inverse() const
{
	const FVectorRegister& A = R[0];
	const FVectorRegister& B = R[1];
	const FVectorRegister& C = R[2];
	const FVectorRegister& D = R[3];

	// C00 = +(fgh / jkl / nop)
	FVectorRegister M00 = Swizzle<1, 2, 3, 3>(B);
	FVectorRegister M01 = Swizzle<1, 2, 3, 3>(C);
	FVectorRegister M02 = Swizzle<1, 2, 3, 3>(D);

	float C00 = Determinant3x3(M00, M01, M02);

	// C01 = -(egh / ikl / mop)
	FVectorRegister M10 = Shuffle<0, 2, 3, 3>(B, B);
	FVectorRegister M11 = Shuffle<0, 2, 3, 3>(C, C);
	FVectorRegister M12 = Shuffle<0, 2, 3, 3>(D, D);

	float C01 = -Determinant3x3(M10, M11, M12);

	// C02 = +(efh / ijl / mnp)
	FVectorRegister M20 = Shuffle<0, 1, 3, 3>(B, B);
	FVectorRegister M21 = Shuffle<0, 1, 3, 3>(C, C);
	FVectorRegister M22 = Shuffle<0, 1, 3, 3>(D, D);

	float C02 = Determinant3x3(M20, M21, M22);

	// C03 = -(efg / ijk / mno)
	float C03 = -Determinant3x3(B, C, D);

	// determinant
	float Det = VectorSIMD::Dot(A, VectorSIMD::SetVal(C00, C01, C02, C03));

	if (FMath::IsNearlyZero(Det))
	{
		return FMatrixRegister::Identity();
	}

	const float InvDet = 1.0f / Det;

	// cofactors

	FVectorRegister C0;
	FVectorRegister C1;
	FVectorRegister C2;
	FVectorRegister C3;

	float C10 =-Determinant3x3(Swizzle<1, 2, 3, 3>(A), Swizzle<1, 2, 3, 3>(C), Swizzle<1, 2, 3, 3>(D));
	float C11 = Determinant3x3(Shuffle<0, 2, 3, 3>(A, A), Shuffle<0, 2, 3, 3>(C, C), Shuffle<0, 2, 3, 3>(D, D));
	float C12 = -Determinant3x3(Shuffle<0, 1, 3, 3>(A, A), Shuffle<0, 1, 3, 3>(C, C), Shuffle<0, 1, 3, 3>(D, D));
	float C13 = Determinant3x3(A, C, D);
	float C20 = Determinant3x3(Swizzle<1, 2, 3, 3>(A), Swizzle<1, 2, 3, 3>(B), Swizzle<1, 2, 3, 3>(D));
	float C21 = -Determinant3x3(Shuffle<0, 2, 3, 3>(A, A), Shuffle<0, 2, 3, 3>(B, B), Shuffle<0, 2, 3, 3>(D, D));
	float C22 = Determinant3x3(Shuffle<0, 1, 3, 3>(A, A), Shuffle<0, 1, 3, 3>(B, B), Shuffle<0, 1, 3, 3>(D, D));
	float C23 = -Determinant3x3(A, B, D);
	float C30 = -Determinant3x3(Swizzle<1, 2, 3, 3>(A), Swizzle<1, 2, 3, 3>(B), Swizzle<1, 2, 3, 3>(C));
	float C31 = Determinant3x3(Shuffle<0, 2, 3, 3>(A, A), Shuffle<0, 2, 3, 3>(B, B), Shuffle<0, 2, 3, 3>(C, C));
	float C32 = -Determinant3x3(Shuffle<0, 1, 3, 3>(A, A), Shuffle<0, 1, 3, 3>(B, B), Shuffle<0, 1, 3, 3>(C, C));
	float C33 = Determinant3x3(A, B, C);
	
	return FMatrixRegister(
		Mul(SetVal(C00, C10, C20, C30),SetVal(InvDet)),
		Mul(SetVal(C01, C11, C21, C31), SetVal(InvDet)),
		Mul(SetVal(C02, C12, C22, C32), SetVal(InvDet)),
		Mul(SetVal(C03, C13, C23, C33), SetVal(InvDet))
	);

}

FMatrix FMatrixRegister::ToFMatrix() const
{
	FMatrix Result;

	VectorSIMD::Store(Result.M[0], R[0]);
	VectorSIMD::Store(Result.M[1], R[1]);
	VectorSIMD::Store(Result.M[2], R[2]);
	VectorSIMD::Store(Result.M[3], R[3]);

	return Result;
}

FMatrixRegister FMatrixRegister::Load(const FMatrix& M)
{
	FMatrixRegister Result;

	Result.R[0] = VectorSIMD::Load(M.M[0]);
	Result.R[1] = VectorSIMD::Load(M.M[1]);
	Result.R[2] = VectorSIMD::Load(M.M[2]);
	Result.R[3] = VectorSIMD::Load(M.M[3]);

	return Result;
}

FMatrixRegister FMatrixRegister::Identity()
{
	FMatrixRegister Result(VectorSIMD::SetVal(1, 0, 0, 0), VectorSIMD::SetVal(0, 1, 0, 0), VectorSIMD::SetVal(0, 0, 1, 0), VectorSIMD::SetVal(0, 0, 0, 1));
	return Result;
}