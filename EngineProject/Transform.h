#pragma once

#include "Math/EngineMath.h"
#include "Rotator.h"

struct FTransform
{
	FTransform() = default;
	FTransform(FVector InL, FVector InS, FRotator InR);

	static FTransform Identity;

	FVector Location = FVector(0, 0, 0);
	FVector Scale = FVector(1, 1, 1);
	FRotator Rotation = FRotator(0, 0, 0);
};
