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
    
    float tEnter = fmax(fmax(tMinX, tMinY), tMinZ);   // min 중에 가장 큰 값 (진입점)
    float tExit = fmin(fmin(tMaxX, tMaxY), tMaxZ);   // max 중에 가장 작은 값 (이탈점)

    if (tEnter > tExit)
    {   // 충돌 안함
        return false;
    }

    if (tExit < 0.0f)
    {   // 박스가 Ray 뒤에 있을 경우
        return false;
    }

    // 광선이 내부라면 tEnter는 음수. 
    OutT = fmax(0.0f, tEnter);
    return true;
}

bool RayIntersectsTriangle(const FRay& Ray, const FVector& v1, const FVector& v2, const FVector& v3, float& OutT)
{
    constexpr float epsilon = 1e-5f;
    // 평면 정의
    FVector edge1 = v2 - v1;
    FVector edge2 = v3 - v1;

    const FVector normal = FVector::CrossProduct(edge1, edge2);
    FVector RayVector = Ray.Direction;
    if (normal.Dot(RayVector) > 0.0f) // 내적의 결과가 양수면 뒷면임
    {
        return false;
    }

    const FVector rayCrossVec = FVector::CrossProduct(RayVector, edge2);
    float det = FVector::DotProduct(rayCrossVec, edge1);
    if (fabs(det) < epsilon)
    {   // 내적의 결과가 0에 가까우면 180도. 평행한 관계
        return false;
    }


    float invDet = 1.0f / det;
    // 수식: Ray.Origin - v1 = u * edge1 + v * edge2 - t * Ray.Direction
    // 1. u 구하기
    FVector s = Ray.Origin - v1;
    float u = invDet * FVector::DotProduct(s, rayCrossVec);

    if (-epsilon > u || epsilon < u - 1)
    {
        return false;
    }

    FVector sCrossE1 = FVector::CrossProduct(s, edge1);
    float v = invDet * FVector::DotProduct(RayVector, sCrossE1);
        
    if (-epsilon > v || epsilon < u + v - 1)
    {
        return false;
    }

    float t = invDet * FVector::DotProduct(edge2, sCrossE1);

    if (t > epsilon)
    {
        OutT = t;
        return true;
    }

    return false;
}
