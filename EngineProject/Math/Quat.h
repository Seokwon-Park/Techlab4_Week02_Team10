#pragma once
#include "EngineMath.h"

using FQuatRegister = FVectorRegister;

struct FQuat
{
	union
	{
		float V[4];
		struct {
			float X;
			float Y;
			float Z;
			float W;
		};
	};

	FQuat();
	FQuat(float InX, float InY, float InZ, float InW = 1.0f);

	static FQuat Identity();
	static FQuat MakeFromAxisAngle(const FVector& Axis, float AngleRadians);
	static FQuat MakeFromEuler(float Pitch, float Yaw, float Roll);

	FQuat operator*(const FQuat& Other) const;
	FQuat Conjugate() const;
	FQuat Inverse() const;
	FQuat Normalize() const;
	FVector RotateVector(const FVector& V) const;
	FMatrix ToFMatrix() const;

};


