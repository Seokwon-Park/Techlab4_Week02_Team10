#include "EnginePCH.h"
#include "Rotator.h"

FRotator::FRotator()
{
	Pitch = 0; Yaw = 0; Roll = 0;
}

FQuat FRotator::Quaternion() const
{
	return FQuat::MakeFromEuler(Pitch, Yaw, Roll);
}

FMatrix FRotator::RotationMatrix() const
{
	return Quaternion().ToFMatrix();
}