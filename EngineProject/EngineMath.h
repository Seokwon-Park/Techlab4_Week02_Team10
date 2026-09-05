#pragma once
#include <cmath>

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