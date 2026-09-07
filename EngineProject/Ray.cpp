#include "EnginePCH.h"
#include "Ray.h"
#include "Math/EngineMath.h"

bool RayIntersectsAABB(const FRay& Ray, const FVector& BoxMin, const FVector& BoxMax, float& OutT)
{
    float tX1 = (BoxMin.X - Ray.Origin.X) / Ray.Direction.X;
    float tX2 = (BoxMax.X - Ray.Origin.X) / Ray.Direction.X;
    float tMinX = fmin(tX1, tX2);
    float tMaxX = fmax(tX1, tX2);

    float tY1 = (BoxMin.Y - Ray.Origin.Y) / Ray.Direction.Y;
    float tY2 = (BoxMax.Y - Ray.Origin.Y) / Ray.Direction.Y;
    float tMinY = fmin(tY1, tY2);
    float tMaxY = fmax(tY1, tY2);

    float tZ1 = (BoxMin.Z - Ray.Origin.Z) / Ray.Direction.Z;
    float tZ2 = (BoxMax.Z - Ray.Origin.Z) / Ray.Direction.Z;
    float tMinZ = fmin(tZ1, tZ2);
    float tMaxZ = fmax(tZ1, tZ2);   
    
    float maxOfMin = fmax(fmax(tMinX, tMinY), tMinZ);   // min 중에 가장 큰 값 (진입점)
    float minOfMax = fmin(fmin(tMaxX, tMaxY), tMaxZ);   // max 중에 가장 작은 값 (이탈점)

    if (maxOfMin > minOfMax)
    {   // 충돌 안함
        return false;
    }

    if (minOfMax < 0.0f)
    {   // 박스가 Ray 뒤에 있을 경우
        return false;
    }


    OutT = fmax(0.0f, minOfMax);
    return true;
}
