#pragma once
#include "Math/EngineMath.h"

// Degree but Quat: Radians
struct FRotator
{
	union
	{
		struct
		{
			float V[3];
			float Pitch;
			float Yaw;
			float Roll;
		};
	};
	FRotator();

	FQuat Quaternion() const;
	FMatrix RotationMatrix() const;

};


