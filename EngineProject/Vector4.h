#pragma once
#include "Vector.h"
#include <iostream>

struct FVector4 {
	float X;
	float Y;
	float Z;
	float W;
	const int NumComponents = 4;

public:
	/* Constructor */
	FVector4();
	FVector4(float x, float y, float z, float w);
	explicit FVector4(float f);
	FVector4(const FVector4& V1);
	FVector4(const FVector& V1, float w = 0.0f);
	// ~FVector();

public:
	/* Public Functions */
	void Set(float x, float y, float z, float w);
	// 벡터를 받는 경우 추가
	void Set(const FVector& V1, float w = 0.0f);
	void Set(const FVector4& V1);

	float Size(); // 길이 반환
	float Length(); // ==  size()
	void Normalize();

	float& Component(int index);		// 참조자 반환으로 lvalue로 직접 값수정 가능
	float Component(int index) const;

	float Dot(const FVector4& V1) const;
	FVector4 Cross(const FVector4& V1) const;
	FVector4 GetAbs();

	// float GetMax();
	//// float GetMin();
	// float GetAbsMax();
	// float GetAbsMin();

	// GetSafeNormal
	// IsNearlyZero
	// Equals
	// ClampSize


/* operator */

	FVector4 operator - ();
	FVector4& operator = (const FVector4& V1);
	FVector4 operator - (const FVector4& V1) const;
	FVector4& operator -= (const FVector4& V1);
	FVector4 operator + (const FVector4& V1) const;
	FVector4& operator += (const FVector4& V1);
	FVector4 operator * (const FVector4& V1) const;
	FVector4 operator * (const float& f) const;
	FVector4& operator *= (const FVector4& V1);
	FVector4& operator *= (const float& f);
	FVector4 operator / (const FVector4& V1) const;
	FVector4 operator / (const float& f) const;
	FVector4& operator /= (const FVector4& V1);
	FVector4& operator /= (const float& f);

	FVector4 operator ^ (const FVector4& V1) const;

	bool operator == (const FVector4& V1) const;
	bool operator != (const FVector4& V1) const;

	float operator[] (int Index) const;
	float& operator[] (int Index);

	/* Static */
	static float DotProduct(const FVector4& V1, const FVector4& V2);
	static FVector4 CrossProduct(const FVector4& V1, const FVector4& V2);
	static float Distance(const FVector4& V1, const FVector4& V2); // == Dist()
	/*static FVector DegreesToRadians(const FVector& V1);
	static FVector RadiansToDegrees(const FVector& V1);
	static FVector Max(const FVector& V1, const FVector& V2);
	static FVector Max3(const FVector& V1, const FVector& V2, const FVector& V3);
	static FVector Min(const FVector& V1, const FVector& V2);
	static FVector Min3(const FVector& V1, const FVector& V2, const FVector& V3);

	static FVector UnitX();
	static FVector UnitY();
	static FVector UnitZ();

	static FVector Zero();*/

};

/* Global Operator */
std::ostream& operator<<(std::ostream& OS, const FVector4& V);

/* constants */
//inline static const FVector4 BackwardVector = FVector4(-1.0f, 0.0f, 0.0f);
//inline static const FVector4 DownVector = FVector4(0.0f, 0.0f, -1.0f);
//inline static const FVector4 ForwardVector = FVector4(1.0f, 0.0f, 0.0f);
//inline static const FVector4 LeftVector = FVector4(0.0f, -1.0f, 0.0f);
//inline static const FVector4 OneVector = FVector4(1.0f, 1.0f, 1.0f);
//inline static const FVector4 RightVector = FVector4(0.0f, 1.0f, 0.0f);
//inline static const FVector4 UpVector = FVector4(0.0f, 0.0f, 1.0f);
//inline static const FVector4 XAxisVector = FVector4(1.0f, 0.0f, 0.0f);
//inline static const FVector4 YAxisVector = FVector4(0.0f, 1.0f, 0.0f);
//inline static const FVector4 ZAxisVector = FVector4(0.0f, 0.0f, 1.0f);
//inline static const FVector4 ZeroVector = FVector4(0.0f, 0.0f, 0.0f);