#include "EnginePCH.h"
#include "Vector.h"

#include <limits>
#include <cmath>
#include <assert.h>

FVector::FVector()
{
	X = 0.0f;
	Y = 0.0f;
	Z = 0.0f;
}

FVector::FVector(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
}

FVector::FVector(float f)
{
	X = f;
	Y = f;
	Z = f;
}

FVector::FVector(const FVector& V1)
{
	X = V1.X;
	Y = V1.Y;
	Z = V1.Z;
}

void FVector::Set(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
}

float FVector::Size()
{
	float sum = X * X + Y * Y + Z * Z;
	return sqrt(sum);
}

float FVector::Length()
{
	float sum = X * X + Y * Y + Z * Z;
	return sqrt(sum);
}

void FVector::Normalize()
{
	float size = this->Size();
	X /= size;
	Y /= size;
	Z /= size;
}

float& FVector::Component(int index)
{
	assert(index >= 0 && index <= 2);
	if (index == 0) return X;
	if (index == 1) return Y;
	if (index == 2) return Z; 
	return X;					// 예외의 경우에서 X를 반환 (임시)
}

float FVector::Component(int index) const
{
	assert(index >= 0 && index <= 2);
	if (index == 0) return X;
	if (index == 1) return Y;
	if (index == 2) return Z;
	return 0.0f;				// 이외의 경우에서 0을 반환 (임시)
}

float FVector::Dot(const FVector& V1) const
{
	return X * V1.X + Y * V1.Y + Z * V1.Z;
}

FVector FVector::Cross(const FVector& V1) const
{
	return FVector(Y*V1.Z - Z*V1.Y, Z*V1.X - X*V1.Z, X*V1.Y - Y * V1.X);
}


FVector FVector::GetAbs() {
	float AbsX = 0.0f;
	float AbsY = 0.0f;
	float AbsZ = 0.0f;
	if (X < 0) AbsX = -X;
	if (Y < 0) AbsY = -Y;
	if (Z < 0) AbsZ = -Z;
	return FVector(AbsX, AbsY, AbsZ);
}

/* Operator */

FVector FVector::operator - () 
{
	return FVector(-X, -Y, -Z);
}

FVector& FVector::operator = (const FVector& V1) 
{
	X = V1.X;
	Y = V1.Y;
	Z = V1.Z;
	return *this;
}

FVector FVector::operator - (const FVector& V1) const
{
	return FVector(X - V1.X, Y - V1.Y, Z - V1.Z);
}

FVector& FVector::operator -= (const FVector& V1)
{
	X -= V1.X;
	Y -= V1.Y;
	Z -= V1.Z;
	return *this;
}

FVector FVector::operator + (const FVector& V1) const
{
	return FVector(X + V1.X, Y + V1.Y, Z + V1.Z);
}

FVector& FVector::operator += (const FVector& V1)
{
	X += V1.X;
	Y += V1.Y;
	Z += V1.Z;
	return *this;
}

FVector FVector::operator * (const FVector& V1) const
{
	return FVector(X * V1.X, Y * V1.Y, Z * V1.Z);
}

FVector& FVector::operator *= (const FVector& V1)
{
	X *= V1.X;
	Y *= V1.Y;
	Z *= V1.Z;
	return *this;
}

FVector& FVector::operator *= (const float& f)
{
	X *= f;
	Y -= f;
	Z -= f;
	return *this;
}

FVector FVector::operator * (const float& f) const
{
	return FVector(X * f, Y * f, Z * f);
}

FVector FVector::operator / (const FVector& V1) const
{
	assert(V1.X != 0 || V1.Y != 0 || V1.Z != 0);
	return FVector(X / V1.X, Y / V1.Y, Z / V1.Z);
}

FVector FVector::operator / (const float& f) const
{
	return FVector(X / f, Y / f, Z / f);
}

FVector& FVector::operator /= (const FVector& V1)
{
	X /= V1.X;
	Y /= V1.Y;
	Z /= V1.Z;
	return *this;
}

FVector& FVector::operator /= (const float& f)
{
	X /= f;
	Y /= f;
	Z /= f;
	return *this;
}

// 스트림 출력 연산자와 함께 사용할 시 괄호로 묶을 것
FVector FVector::operator ^ (const FVector& V1) const
{
	return this->Cross(V1);
}

bool FVector::operator == (const FVector& V1) const
{
	if (this->X == V1.X && this->Z == V1.Z && this->Y == V1.Y)
		return true;
	else
		return false;
}

bool FVector::operator != (const FVector& V1) const
{
	if (this->X == V1.X && this->Z == V1.Z && this->Y == V1.Y)
		return false;
	else
		return true;
}

float FVector::operator[] (int Index) const
{
	return this->Component(Index);
}

float& FVector::operator[] (int Index) 
{
	return this->Component(Index);
}

/* Global Operator */
std::ostream& operator << (std::ostream & OS, const FVector & V)
{
	OS << "X: " << V.X << " Y: " << V.Y << " Z: " << V.Z;
	return OS;
}


/* Static Functions */

float FVector::DotProduct(const FVector& V1, const FVector& V2)
{
	return V1.Dot(V2);
}

FVector FVector::CrossProduct(const FVector& V1, const FVector& V2)
{
	return V1.Cross(V2);
}

float FVector::Distance(const FVector& V1, const FVector& V2)
{
	float dX = V1.X - V2.X;
	float dY = V1.Y - V2.Y;
	float dZ = V1.Z - V2.Z;
	float sum = dX * dX + dY * dY + dZ * dZ;

	return sqrt(sum);
}
