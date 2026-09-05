#pragma once

#include "Ray.h"
#include "Matrix.h"
#include "Vector.h"

class Picking
{
public:
	static FRay ScreenToRay(int32 MouseX, int32 MouseY, int32 ScreenWidth, int32 ScreenHeight, const FMatrix& View, const FMatrix& Proj);
};