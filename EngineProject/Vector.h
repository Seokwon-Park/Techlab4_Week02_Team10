#pragma once
#include <iostream>

struct FVector {
	float X;
	float Y;
	float Z;
	const int NumComponents = 3;

public:
/* Constructor */
	FVector();
	FVector(float x, float y, float z);
	explicit FVector(float f);
	FVector(const FVector& V1);
	// ~FVector();

public:
/* Public Functions */
	void Set(float x, float y, float z);

	float Size(); // 길이 반환
	float Length(); // ==  size()
	void Normalize();

	float& Component(int index);		// 참조자 반환으로 lvalue로 직접 값수정 가능
	float Component(int index) const;

	float Dot(const FVector& V1) const;
	FVector Cross(const FVector& V1) const;
	FVector GetAbs();

	// float GetMax();
	//// float GetMin();
	// float GetAbsMax();
	// float GetAbsMin();

	// GetSafeNormal
	// IsNearlyZero
	// Equals
	// ClampSize


/* operator */

	FVector operator - ();
	FVector& operator = (const FVector& V1);
	FVector operator - (const FVector& V1) const;
	FVector& operator -= (const FVector& V1);
	FVector operator + (const FVector& V1) const;
	FVector& operator += (const FVector& V1);
	FVector operator * (const FVector& V1) const;
	FVector operator * (const float& f) const;
	FVector& operator *= (const FVector& V1);
	FVector& operator *= (const float & f);
	FVector operator / (const FVector& V1) const;
	FVector operator / (const float& f) const;
	FVector& operator /= (const FVector& V1);
	FVector& operator /= (const float& f);

	FVector operator ^ (const FVector& V1) const;

	bool operator == (const FVector& V1) const;
	bool operator != (const FVector& V1) const;

	float operator[] (int Index) const;
	float& operator[] (int Index);

/* Static */
	static float DotProduct(const FVector& V1, const FVector& V2);
	static FVector CrossProduct(const FVector& V1, const FVector& V2);
	static float Distance(const FVector& V1, const FVector& V2); // == Dist()
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
std::ostream& operator<<(std::ostream& OS, const FVector& V);

/* constants */
inline static const FVector BackwardVector = FVector(-1.0f, 0.0f, 0.0f);
inline static const FVector DownVector = FVector(0.0f, 0.0f, -1.0f);
inline static const FVector ForwardVector = FVector(1.0f, 0.0f, 0.0f);
inline static const FVector LeftVector = FVector(0.0f, -1.0f, 0.0f);
inline static const FVector OneVector = FVector(1.0f, 1.0f, 1.0f);
inline static const FVector RightVector = FVector(0.0f, 1.0f, 0.0f);
inline static const FVector UpVector = FVector(0.0f, 0.0f, 1.0f);
inline static const FVector XAxisVector = FVector(1.0f, 0.0f, 0.0f);
inline static const FVector YAxisVector = FVector(0.0f, 1.0f, 0.0f);
inline static const FVector ZAxisVector = FVector(0.0f, 0.0f, 1.0f);
inline static const FVector ZeroVector = FVector(0.0f, 0.0f, 0.0f);