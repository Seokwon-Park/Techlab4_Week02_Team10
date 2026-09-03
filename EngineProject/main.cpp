#include <Windows.h>
#include "Engine.h"

//LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//    if (msg == WM_DESTROY)
//    {
//        PostQuitMessage(0);
//        return 0;
//    }
//    return DefWindowProc(hwnd, msg, wParam, lParam);
//}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    TUniquePtr<Engine> engine = MakeUnique<Engine>();
    if (!engine->Init(hInstance)) return -1;

    engine->Run();
    engine->Shutdown();


    return 0;
}