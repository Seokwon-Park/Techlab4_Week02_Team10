#pragma once
#include <cmath>
#include "Vector.h"
#include "Vector4.h"
#include "Matrix.h"
#include "VectorRegister.h"
#include "MatrixRegister.h"

namespace FMath
{
	static inline bool IsNearlyZero(float Value, float ErrorTolerance = 1e-4f)
	{
		return std::abs(Value) <= ErrorTolerance;
	}

	static inline bool IsNearlyEqual(float Value1, float Value2, float ErrorTolerance = 1e-4f)
	{
		return std::abs(Value1 - Value2) <= ErrorTolerance;
	}
}