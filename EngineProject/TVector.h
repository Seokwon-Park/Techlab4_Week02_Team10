//#pragma once
//
//#include "Types.h"
//
//template<typename T>
//struct TVector {
//
//	union
//	{
//		T V[3];
//		struct
//		{
//			T X;
//			T Y;
//			T Z;
//		};
//	};
//
//public:
//	/* Constructor */
//	TVector()
//	{
//		X = T(0);
//		Y = T(0);
//		Z = T(0);
//	}
//	TVector(T x, T y, T z)
//	{
//		X = x;
//		Y = y;
//		Z = z;
//	}
//	explicit TVector(T f)
//	{
//		X = t;
//		Y = t;
//		Z = t;
//	}
//	TVector(const TVector& V1)
//	{
//		X = V1.X;
//		Y = V1.Y;
//		Z = V1.Z;
//	}
//
//public:
//	/* Public Functions */
//	void Set(T x, T y, T z)
//	{
//		X = x;
//		Y = y;
//		Z = z;
//	}
//
//	T Size() const // 길이 반환
//	{
//		T sum = X * X + Y * Y + Z * Z;
//		return sqrt(sum);
//	}
//
//	T Length() const // ==  size()
//	{
//		T sum = X * X + Y * Y + Z * Z;
//		return sqrt(sum);
//	}
//	
//	T Dot(const TVector<T>& V1) const
//	{
//		return X * V1.X + Y * V1.Y + Z * V1.Z;
//	}
//
//	TVector<T> Cross(const TVector<T>& V1) const
//	{
//		return TVector<T>(Y * V1.Z - Z * V1.Y, Z * V1.X - X * V1.Z, X * V1.Y - Y * V1.X);
//	}
//
//	TVector<T> GetAbs() const
//	{
//		T AbsX = X;
//		T AbsY = Y;
//		T AbsZ = Z;
//		if (X < 0) AbsX = -X;
//		if (Y < 0) AbsY = -Y;
//		if (Z < 0) AbsZ = -Z;
//		return FVector(AbsX, AbsY, AbsZ);
//	}
//
//	TVector<T> Normalize() const
//	{
//		T size = Size();
//
//		if (!FMath::IsNearlyZero(size))
//		{
//			return FVector(X / size, Y / size, Z / size);
//		}
//
//		return *this;
//	}
//
//
///* operator */
//
//	TVector<T> operator - ()
//	{
//		return TVector<T>(-X, -Y, -Z);
//	}
//
//	TVector<T>& operator = (const TVector<T>& V1)
//	{
//		X = V1.X;
//		Y = V1.Y;
//		Z = V1.Z;
//		return *this;
//	}
//
//	TVector<T> operator - (const TVector<T>& V1) const
//	{
//		return TVector<T>(X - V1.X, Y - V1.Y, Z - V1.Z);
//	}
//
//	TVector<T>& operator -= (const TVector<T>& V1)
//	{
//		X -= V1.X;
//		Y -= V1.Y;
//		Z -= V1.Z;
//		return *this;
//	}
//
//	TVector<T> operator + (const TVector<T>& V1) const;
//	{
//		return TVector<T>(X + V1.X, Y + V1.Y, Z + V1.Z);
//	}
//
//
//	TVector<T>& operator += (const TVector<T>& V1);
//	{
//		X += V1.X;
//		Y += V1.Y;
//		Z += V1.Z;
//		return *this;
//	}
//
//	TVector<T> operator * (const TVector<T>& V1) const
//	{
//		return FVector(X * V1.X, Y * V1.Y, Z * V1.Z);
//	}
//
//	TVector<T> operator * (const T& f) const
//
//
//	TVector<T>& operator *= (const TVector<T>& V1)
//	{
//		X *= V1.X;
//		Y *= V1.Y;
//		Z *= V1.Z;
//		return *this;
//	}
//
//	TVector<T>& operator *= (const T& f)
//
//
//	TVector<T> operator / (const TVector<T>& V1) const;
//	TVector<T> operator / (const T& f) const;
//	TVector<T>& operator /= (const TVector<T>& V1);
//	TVector<T>& operator /= (const T& f);
//
//	TVector<T> operator ^ (const TVector<T>& V1) const;
//
//	bool operator == (const TVector<T>& V1) const;
//	bool operator != (const TVector<T>& V1) const;
//
//	T operator[] (int32 Index) const;
//	T& operator[] (int32 Index);
//
//	/* Static */
//	static T DotProduct(const TVector<T>& V1, const TVector<T>& V2);
//	static TVector<T> CrossProduct(const TVector<T>& V1, const TVector<T>& V2);
//	static T Distance(const TVector<T>& V1, const TVector<T>& V2); // == Dist()
//
//};