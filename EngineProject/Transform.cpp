#include "EnginePCH.h"
#include "Transform.h"

FTransform::FTransform(FVector InL, FVector InS, FQuat InQ)
{
	Location = InL;
	Scale = InS;
	Rotation = InQ;
}

FTransform::FTransform(FVector InL, FVector InS, FRotator InR)
{
	Location = InL;
	Scale = InS;
	Rotation = InR.Quaternion();
}

FTransform FTransform::Identity = FTransform(FVector(0, 0, 0), FVector(1, 1, 1), FQuat(0, 0, 0));