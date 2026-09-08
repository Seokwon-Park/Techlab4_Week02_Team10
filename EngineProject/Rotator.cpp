#include "EnginePCH.h"
#include "Rotator.h"
#include "Math/EngineMath.h"

FRotator::FRotator()
{
	Pitch = 0; Yaw = 0; Roll = 0;
}

FRotator::FRotator(float P, float Y, float R)
{
	Pitch = P; Yaw = Y; Roll = R;
}


FQuat FRotator::Quaternion() const
{
	// Degree를 Radian으로 변환
	float PRad = Pitch * (PI / 180.0f);
	float YRad = Yaw * (PI / 180.0f);
	float RRad = Roll * (PI / 180.0f);
	
	return FQuat::MakeFromEuler(RRad, PRad, YRad);
}

FMatrix FRotator::RotationMatrix() const
{
	return Quaternion().ToFMatrix();
}

FRotator FRotator::Identitiy = FRotator(0, 0, 0);