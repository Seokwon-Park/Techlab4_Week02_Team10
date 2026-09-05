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
    
    FVector4 V(1.0f, 2.0f, 3.0f, 1.0f);

    FMatrix M(
        1.0f, 0.0f, 0.0f, 10.0f,
        0.0f, 1.0f, 0.0f, 20.0f,
        0.0f, 0.0f, 1.0f, 30.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );

    // Matrix.TransformFVector4(Vector4)
    FVector4 Result1 = M.TransformFVector4(V);

    // Vector4 * Matrix
    FVector4 Result2 = V * M;

    // Matrix * Vector4
    FVector4 Result3 = M * V;

    std::cout << "==============================" << std::endl;

    std::cout << "Vector V : " << V << std::endl;
    std::cout << "Matrix M :" << std::endl;
    std::cout << M << std::endl;

    std::cout << "==============================" << std::endl;

    std::cout << "M.TransformFVector4(V) : "
        << Result1 << std::endl;

    std::cout << "V * M                  : "
        << Result2 << std::endl;

    std::cout << "M * V                  : "
        << Result3 << std::endl;

    std::cout << "==============================" << std::endl;

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