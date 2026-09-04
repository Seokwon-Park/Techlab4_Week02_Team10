#include <Windows.h>
#include "Engine.h"

//#include <iostream>
#include "Vector.h"
#include "Vector4.h"

int main()
{
    HINSTANCE hInstance = GetModuleHandle(nullptr);

    TUniquePtr<Engine> engine = MakeUnique<Engine>();
    if (!engine->Init(hInstance)) return -1;

    engine->Run();
    engine->Shutdown();

    /*FVector V1(6.0f, 2.0f, 3.0f);
    FVector V2 = FVector(5.0f, 3.0f, 2);

    std::cout << "V1[0] << V2[2]: " << V1[0] << V2[2] << '\n';;
    std::cout << "V1: " << V1 << '\n';
    std::cout << "V2: " << V2 << '\n';

    std::cout << "V1 + V2: " << V1 + V2 << '\n';
    std::cout << "V1 - V2 " <<  V1 - V2 << '\n';
    std::cout << "V1 * V2: " << V1 * V2 << '\n';
    std::cout << "V1 / V2: " << V1 / V2 << '\n';

    std::cout << "V1 * 2: " << V1 * 2 << '\n';
    std::cout << "V1 / 3: " << V1 / 3 << '\n';


    std::cout << "-V1" << - V1 << '\n';

    std::cout << "V1 -= V2: ";
    V1 -= V2;
    std::cout << V1 << '\n';

    std::cout << "V1 += V2: ";
    V1 += V2;
    std::cout << V1 << '\n';

    std::cout << "V1 *= V2: ";
    V1 *= V2;
    std::cout << V1 << '\n';

    std::cout << "V1 /= V2: ";
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

    std::cout << "V1[0] << V2[2]: " << V1[0] << V2[2] << '\n';;
    std::cout << "V1: " << V1 << '\n';
    std::cout << "V2: " << V2 << '\n';

    std::cout << "V1 + V2: " << V1 + V2 << '\n';
    std::cout << "V1 - V2 " << V1 - V2 << '\n';
    std::cout << "V1 * V2: " << V1 * V2 << '\n';
    std::cout << "V1 / V2: " << V1 / V2 << '\n';

    std::cout << "V1 * 2: " << V1 * 2 << '\n';
    std::cout << "V1 / 3: " << V1 / 3 << '\n';*/

    // Vector4 Debug
    FVector4 V1(1.0f, 2.0f, 3.0f, 4.0f);
    FVector4 V2 = FVector4(5.0f, 3.0f, 2.0f, 7);
    FVector V3 = FVector(1.0f, 1.0f, 1.0f);
    FVector4 V4(V3);
    std::cout << "V4: " << V4 << '\n';

    std::cout << "-------Vector4-------" << '\n';
    std::cout << "V1[0] << V2[2]: " << V1[0] << V2[2] << '\n';;
    std::cout << "V1: " << V1 << '\n';
    std::cout << "V2: " << V2 << '\n';

    std::cout << "V1 + V2: " << V1 + V2 << '\n';
    std::cout << "V1 - V2 " << V1 - V2 << '\n';
    std::cout << "V1 * V2: " << V1 * V2 << '\n';
    std::cout << "V1 / V2: " << V1 / V2 << '\n';

    std::cout << "V1 * 2: " << V1 * 2 << '\n';
    std::cout << "V1 / 3: " << V1 / 3 << '\n';

    std::cout << "-V1" << -V1 << '\n';

    std::cout << "V1 -= V2: ";
    V1 -= V2;
    std::cout << V1 << '\n';

    std::cout << "V1 += V2: ";
    V1 += V2;
    std::cout << V1 << '\n';

    std::cout << "V1 *= V2: ";
    V1 *= V2;
    std::cout << V1 << '\n';

    std::cout << "V1 /= V2: ";
    V1 /= V2;
    std::cout << V1 << '\n';

    std::cout << "cross" << '\n';
    std::cout << (V1 ^ V2) << '\n';
    std::cout << FVector4::CrossProduct(V1, V2) << '\n';

    std::cout << "Dot" << '\n';
    std::cout << V1.Dot(V2) << '\n';
    std::cout << FVector4::DotProduct(V1, V2) << '\n';

    std::cout << "Length" << '\n';
    std::cout << V1.Size() << '\n';
    std::cout << V1.Length() << '\n';

    std::cout << "Normal" << '\n';
    V1.Normalize();
    std::cout << V1 << '\n';


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