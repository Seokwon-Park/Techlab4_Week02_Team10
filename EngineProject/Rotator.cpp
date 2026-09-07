#include "EnginePCH.h"
#include "Rotator.h"

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
	return FQuat::MakeFromEuler(Pitch, Yaw, Roll);
}

FMatrix FRotator::RotationMatrix() const
{
	return Quaternion().ToFMatrix();
}

FRotator FRotator::Identitiy = FRotator(0, 0, 0);