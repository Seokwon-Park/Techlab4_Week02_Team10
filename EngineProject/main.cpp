#include "EnginePCH.h"

#include <Windows.h>
#include "Engine.h"

#include "Matrix.h"
#include "EngineMath.h"
#include <assert.h>


int main()
{
    HINSTANCE hInstance = GetModuleHandle(nullptr);

    TUniquePtr<Engine> engine = MakeUnique<Engine>();
    if (!engine->Init(hInstance)) return -1;

    engine->Run();
    engine->Shutdown();
    
    std::cout << "==================================================\n";
    std::cout << "            FVector DEBUG TEST SUITE              \n";
    std::cout << "==================================================\n\n";

    // 1. Constructors & Stream Output
    std::cout << "[1] Constructors & Stream Output Test\n";
    FVector VDef;
    FVector VParam(1.0f, 2.0f, 3.0f);
    FVector VScalar(5.0f);
    FVector VCopy(VParam);

    std::cout << "Default       : " << VDef << " (Expected: (0, 0, 0))\n";
    std::cout << "Param         : " << VParam << " (Expected: (1, 2, 3))\n";
    std::cout << "Scalar        : " << VScalar << " (Expected: (5, 5, 5))\n";
    std::cout << "Copy          : " << VCopy << " (Expected: (1, 2, 3))\n\n";

    assert(FMath::IsNearlyZero(VDef.X) && FMath::IsNearlyZero(VDef.Y) && FMath::IsNearlyZero(VDef.Z));
    assert(FMath::IsNearlyEqual(VParam.X, 1.0f) && FMath::IsNearlyEqual(VParam.Y, 2.0f) && FMath::IsNearlyEqual(VParam.Z, 3.0f));

    // 2. Component & Accessors
    std::cout << "[2] Accessors & Component Test\n";
    FVector VAccess(10.0f, 20.0f, 30.0f);
    assert(FMath::IsNearlyEqual(VAccess.Component(0), 10.0f));
    assert(FMath::IsNearlyEqual(VAccess.Component(1), 20.0f));
    assert(FMath::IsNearlyEqual(VAccess.Component(2), 30.0f));
    std::cout << "Component(0,1,2) : " << VAccess.Component(0) << ", " << VAccess.Component(1) << ", " << VAccess.Component(2) << "\n\n";

    // 3. Magnitude & Normalization
    std::cout << "[3] Length & Normalize Test\n";
    FVector VLen(3.0f, 4.0f, 0.0f); // Length = 5
    float Length = VLen.Length();
    std::cout << "Length of (3,4,0): " << Length << " (Expected: 5)\n";
    assert(FMath::IsNearlyEqual(Length, 5.0f));

    VLen.Normalize();
    std::cout << "Normalized      : " << VLen << " (Expected: (0.6, 0.8, 0))\n";
    assert(FMath::IsNearlyEqual(VLen.X, 0.6f) && FMath::IsNearlyEqual(VLen.Y, 0.8f));
    assert(FMath::IsNearlyEqual(VLen.Length(), 1.0f));
    std::cout << "PASSED: Normalization verified.\n\n";

    // 4. Vector Math (Dot, Cross, Distance)
    std::cout << "[4] Dot Product, Cross Product & Distance Test\n";
    FVector A(1.0f, 0.0f, 0.0f);
    FVector B(0.0f, 1.0f, 0.0f);

    float DotResult = FVector::DotProduct(A, B);
    FVector CrossResult = FVector::CrossProduct(A, B);
    float Dist = FVector::Distance(A, B); // sqrt(1^2 + 1^2) = sqrt(2) ≈ 1.41421

    std::cout << "Dot(A, B)        : " << DotResult << " (Expected: 0)\n";
    std::cout << "Cross(A, B)      : " << CrossResult << " (Expected: (0, 0, 1))\n";
    std::cout << "Distance(A, B)   : " << Dist << " (Expected: ~1.41421)\n";

    assert(FMath::IsNearlyZero(DotResult));
    assert(FMath::IsNearlyEqual(CrossResult.Z, 1.0f));
    assert(FMath::IsNearlyEqual(Dist, std::sqrt(2.0f)));
    std::cout << "PASSED: Vector math operations verified.\n\n";

    // 5. Binary Arithmetic & Assignment Operators
    std::cout << "[5] Arithmetic & Assignment Operators Test\n";
    FVector V1(10.0f, 20.0f, 30.0f);
    FVector V2(2.0f, 4.0f, 5.0f);

    assert((V1 + V2) == FVector(12.0f, 24.0f, 35.0f));
    assert((V1 - V2) == FVector(8.0f, 16.0f, 25.0f));
    assert((V1 * V2) == FVector(20.0f, 80.0f, 150.0f));
    assert((V1 / V2) == FVector(5.0f, 5.0f, 6.0f));
    assert((V1 * 2.0f) == FVector(20.0f, 40.0f, 60.0f));
    assert((V1 / 2.0f) == FVector(5.0f, 10.0f, 15.0f));

    FVector VAssign = V1;
    VAssign += V2;
    assert(VAssign == FVector(12.0f, 24.0f, 35.0f));
    VAssign -= V2;
    assert(VAssign == V1);
    std::cout << "PASSED: All arithmetic operators verified.\n\n";

    // 6. Comparison Operators & Bug Assert Checks
    std::cout << "[6] Comparison & Edge-Case Division Test\n";
    FVector CompA(10.0f, 20.0f, 30.0f);
    FVector CompB(10.0f, 20.0f, 99.0f);

    std::cout << "CompA == CompB   : " << (CompA == CompB ? "true" : "false") << " (Expected: false)\n";
    std::cout << "CompA != CompB   : " << (CompA != CompB ? "true" : "false") << " (Expected: true)\n";

    assert((CompA == CompB) == false);
    assert((CompA != CompB) == true);

    // Division Assert Check Notice
    std::cout << "\n[Notice] Checking Vector Division Assert Rule:\n";
    std::cout << "Ensure 'operator/' uses AND logic (&&) for zero-checks.\n";
    std::cout << "Example: assert(V1.X != 0 && V1.Y != 0 && V1.Z != 0);\n\n";

    std::cout << "==================================================\n";
    std::cout << "              TEST SUITE COMPLETE                 \n";
    std::cout << "==================================================\n";

    return 0;
    
}

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
//    LPSTR lpCmdLine, int nCmdShow)
//{
//    TUniquePtr<Engine> engine = MakeUnique<Engine>();
//    if (!engine->Init(hInstance)) return -1;
//
//    engine->Run();
//    engine->Shutdown();
//
//
//    return 0;
//}