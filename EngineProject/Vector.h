#pragma once

struct FVector {
	float X;
	float Y;
	float Z;
public:
	// Constructor
	FVector();
	FVector(int x, int y, int z);
	FVector(float x, float y, float z);
	FVector(float f);
	// FVector(FVector V1);
	// ~FVector();

private:
	// constants
	// const FVector BackwardVector = FVector( -1.0f, 0.0f, 0.0f );

public:
	void Set(float x, float y, float z);

	float Size(); // 길이 반환
	void Normalize();

	float& Component(int index);		// 참조자 반환으로 lvalue로 직접 값수정 가능
	float Component(int index) const;

	float GetMax();
	float GetMin();

	float Dot(const FVector& V1) const;
	FVector Cross(const FVector& V1) const;

	FVector GetAbs();

	// FVector 

	// GetSafeNormal
	// IsNearlyZero
	// Equals
	// ClampSize

public:
	// operator
	FVector& operator = (const FVector& V1);
	FVector operator - (const FVector& V1) const;
	FVector operator + (const FVector& V1) const;
	FVector operator * (const FVector& V1) const;
	FVector operator * (const float& f) const;
	FVector operator / (const FVector& V1) const;
	FVector operator / (const float& f) const;
	// ^ : Cross Product
	FVector operator ^ (const FVector& V1) const;

	bool operator == (const FVector& V1) const;
	bool operator != (const FVector& V1) const;

	float operator[] (int Index) const;
	float& operator[] (int Index);
	

public:
	static float DotProduct(const FVector& V1, const FVector& V2);
	static FVector CrossProduct(const FVector& V1, const FVector& V2);
	static float Distance(const FVector& V1, const FVector& V2); // == Dist()
	static FVector DegreesToRadians(const FVector& V1);
	static FVector RadiansToDegrees(const FVector& V1);
	static FVector Max(const FVector& V1, const FVector& V2);
	static FVector Max3(const FVector& V1, const FVector& V2, const FVector& V3);
	static FVector Min(const FVector& V1, const FVector& V2);
	static FVector Min3(const FVector& V1, const FVector& V2, const FVector& V3);
	
	static FVector UnitX();
	static FVector UnitY();
	static FVector UnitZ();

	static FVector Zero();
};