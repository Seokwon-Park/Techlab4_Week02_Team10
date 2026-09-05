#pragma once
#include <cmath>

namespace FMath
{
	static inline bool IsNearlyZero(float Value, float ErrorTolerance = 1e-4f)
	{
		return std::abs(Value) <= ErrorTolerance;
	}
}