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

FVector::FVector(int x, int y, int z)
{
	X = static_cast<float>(x);
	Y = static_cast<float>(y);
	Z = static_cast<float>(z);
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
}

float FVector::Component(int index) const
{
	assert(index >= 0 && index <= 2);
	if (index == 0) return X;
	if (index == 1) return Y;
	if (index == 2) return Z;
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

}

/* Operator */

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

FVector FVector::operator + (const FVector& V1) const
{
	return FVector(X + V1.X, Y + V1.Y, Z + V1.Z);
}

FVector FVector::operator * (const FVector& V1) const
{
	return FVector(X * V1.X, Y * V1.Y, Z * V1.Z);
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

FVector FVector::operator ^ (const FVector& V1) const
{
	return this->Cross(V1);
	//return FVector(Y * V1.Z - Z * V1.Y, Z * V1.X - X * V1.Z, X * V1.Y - Y * V1.X);
}

bool FVector::operator == (const FVector& V1) const
{
	if (this->X == V1.X && this->Z == V1.Z && this->Y == V1.Y)
		return true;
	else
		return false;
}

bool FVector::operator == (const FVector& V1) const
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


/* Static Functions */

static float DotProduct(const FVector& V1, const FVector& V2)
{
	return V1.Dot(V2);
}

static FVector CrossProduct(const FVector& V1, const FVector& V2)
{
	return V1.Cross(V2);
}