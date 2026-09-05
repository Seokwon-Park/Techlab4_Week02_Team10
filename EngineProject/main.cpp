#include "EnginePCH.h"

#include <Windows.h>
#include "Engine.h"

#include "Vector.h"
#include "Vector4.h"
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
    
    // ============================================================
    // 1. Local Position
    // ============================================================
    FVector4 LocalPosition(
        1.0f,
        0.0f,
        0.0f,
        1.0f
    );

    // ============================================================
    // 2. World Matrix
    // Scale  : (1, 1, 1)
    // Rotation: Y축 45도
    // Position: (10, 0, 0)
    // ============================================================
    FVector Scale(
        1.0f,
        1.0f,
        1.0f
    );

    FVector Rotation(
        0.0f,
        XMConvertToRadians(45.0f),
        0.0f
    );

    FVector Translation(
        10.0f,
        0.0f,
        0.0f
    );

    FMatrix World = FMatrix::MakeWorld(
        Scale,
        Rotation,
        Translation
    );

    // ============================================================
    // 3. View Matrix
    // Camera : (0, 0, -20)
    // Target : (0, 0, 0)
    // Up     : (0, 1, 0)
    // ============================================================
    FVector Eye(
        0.0f,
        0.0f,
        -20.0f
    );

    FVector Target(
        0.0f,
        0.0f,
        0.0f
    );

    FVector Up(
        0.0f,
        1.0f,
        0.0f
    );

    FMatrix View = FMatrix::MakeView(
        Eye,
        Target,
        Up
    );

    // ============================================================
    // 4. Projection Matrix
    // ============================================================
    float FovY =
        XMConvertToRadians(60.0f);

    float AspectRatio =
        16.0f / 9.0f;

    float NearZ = 0.1f;
    float FarZ = 1000.0f;

    FMatrix Projection =
        FMatrix::MakePerspective(
            FovY,
            AspectRatio,
            NearZ,
            FarZ
        );

    // ============================================================
    // 5. World → View → Projection
    // ============================================================
    FMatrix WVP =
        World *
        View *
        Projection;

    // ============================================================
    // 6. Transform
    // ============================================================
    FVector4 WorldPosition =
        World * LocalPosition;

    FVector4 ViewPosition =
        View * WorldPosition;

    FVector4 ClipPosition =
        Projection * ViewPosition;

    // 또는
    FVector4 ClipPosition2 =
        WVP * LocalPosition;

    // ============================================================
    // Debug
    // ============================================================

    std::cout << "========================================\n";
    std::cout << "Local Position\n";
    std::cout << LocalPosition << "\n\n";

    std::cout << "World Matrix\n";
    std::cout << World << "\n";

    std::cout << "View Matrix\n";
    std::cout << View << "\n";

    std::cout << "Projection Matrix\n";
    std::cout << Projection << "\n";

    std::cout << "WVP Matrix\n";
    std::cout << WVP << "\n";

    std::cout << "========================================\n";

    std::cout << "World Position\n";
    std::cout << WorldPosition << "\n\n";

    std::cout << "View Position\n";
    std::cout << ViewPosition << "\n\n";

    std::cout << "Clip Position\n";
    std::cout << ClipPosition << "\n\n";

    std::cout << "Clip Position 2\n";
    std::cout << ClipPosition2 << "\n";

    std::cout << "========================================\n";

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