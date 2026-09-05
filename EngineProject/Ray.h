#pragma once

#include "Vector.h"

struct FRay
{
	// 광선 시작위치
	FVector Origin;
	// 광선 방향
	FVector Direction;

	FVector PointAt(float t) const
	{
		return Origin + Direction * t;
	}
};

bool RayIntersectsAABB(const FRay& Ray, const FVector& BoxMin, const FVector& BoxMax, float& OutT);