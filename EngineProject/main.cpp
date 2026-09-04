#include <Windows.h>
#include "Engine.h"

//#include <iostream>
#include "Vector.h"

int main()
{
    HINSTANCE hInstance = GetModuleHandle(nullptr);

    TUniquePtr<Engine> engine = MakeUnique<Engine>();
    if (!engine->Init(hInstance)) return -1;

    engine->Run();
    engine->Shutdown();

    FVector V1(6.0f, 2.0f, 3.0f);
    FVector V2 = FVector(5.0f, 3.0f, 2);

    std::cout << V1[0] << V2[2] << '\n';;
    std::cout << V1 << '\n';
    std::cout << V2 << '\n';

    std::cout << V1 + V2 << '\n';
    std::cout << V1 - V2 << '\n';
    std::cout << V1 * V2 << '\n';
    std::cout << V1 / V2 << '\n';

    std::cout << V1 * 2 << '\n';
    std::cout << V1 / 3 << '\n';


    std::cout << -V1 << '\n';

    V1 -= V2;

    std::cout << V1 << '\n';

    V1 += V2;

    std::cout << V1 << '\n';

    V1 *= V2;

    std::cout << V1 << '\n';

    V1 /= V2;

    std::cout << V1 << '\n';

    std::cout << "cross" << '\n';
    std::cout << (V1 ^ V2) << '\n';
    std::cout << FVector::CrossProduct(V1, V2) << '\n';

    std::cout << "Dot" << '\n';
    std::cout << V1.Dot(V2) << '\n';
    std::cout << FVector::DotProduct(V1, V2) << '\n';

    std::cout << "Length" << '\n';
    std::cout << V1.Size() << '\n';
    std::cout << V1.Length() << '\n';

    std::cout << "Normal" << '\n';
    V1.Normalize();
    std::cout << V1<< '\n';




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