#pragma once

#include "VectorRegister.h"

using FQuatRegister = FVectorRegister;

struct FVector;
struct FMatrix;

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

	/* Function */
	FQuat operator * (const FQuat& Other) const;
	FQuat Conjugate() const;
	FQuat UnitInverse() const;
	FQuat Inverse() const;
	FQuat Normalize() const;
	FVector RotateVector(const FVector& V) const;
	FMatrix ToFMatrix() const;

	/* Static */
	static FQuat Identity();
	static FQuat MakeFromAxisAngle(const FVector& Axis, float AngleRadians);
	static FQuat MakeFromEuler(float Pitch, float Yaw, float Roll);
};


