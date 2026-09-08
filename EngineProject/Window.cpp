#include "EnginePCH.h"

#include "Window.h"
#include "InputSystem.h"

#include <backends/imgui_impl_win32.h>

uint32 Width = 1280;
uint32 Height = 720;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_LBUTTONDOWN:
		FInputSystem::OnMouseDown(EMouseButton::Left);
		break;
	case WM_LBUTTONUP:
		FInputSystem::OnMouseUp(EMouseButton::Left);
		break;
	case WM_RBUTTONDOWN:
		FInputSystem::OnMouseDown(EMouseButton::Right);
		break;
	case WM_RBUTTONUP:
		FInputSystem::OnMouseUp(EMouseButton::Right);
		break;
	case WM_MBUTTONDOWN:
		FInputSystem::OnMouseDown(EMouseButton::Middle);
		break;
	case WM_MBUTTONUP:
		FInputSystem::OnMouseUp(EMouseButton::Middle);
		break;
	case WM_XBUTTONDOWN:
	{
		int Button = GET_XBUTTON_WPARAM(wParam); // XBUTTON1 또는 XBUTTON2 매크로
		if (Button == XBUTTON1)
			FInputSystem::OnMouseDown(EMouseButton::Side1);
		else if (Button == XBUTTON2)
			FInputSystem::OnMouseDown(EMouseButton::Side2);
		break;
	}

	case WM_XBUTTONUP:
	{
		int Button = GET_XBUTTON_WPARAM(wParam); // XBUTTON1 또는 XBUTTON2 매크로
		if (Button == XBUTTON1)
			FInputSystem::OnMouseUp(EMouseButton::Side1);
		else if (Button == XBUTTON2)
			FInputSystem::OnMouseUp(EMouseButton::Side2);
		break;
	}
	
	case WM_MOUSEMOVE: 
	{
		//FInputSystem::OnMouseMove((int)(short)LOWORD(lParam) * (Width/1280), (int)(short)HIWORD(lParam) * (Height/720));
		///*POINT Point;
		//GetCursorPos(&Point);
		//ScreenToClient(hWnd, &Point);
		//FInputSystem::OnMouseMove(Point.x, Point.y);*/
		printf("Mouse X: %d, Mouse Y: %d\n", (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam));

		int MouseX = (int)(short)LOWORD(lParam) *(1280.0f / Width);
		int MouseY = (int)(short)HIWORD(lParam) * (720.0f /Height);

		printf("Mouse X(refined): %d, Mouse Y: %d\n", MouseX, MouseY);

		FInputSystem::OnMouseMove(MouseX, MouseY);
	}
		break;

	case WM_MOUSEWHEEL:
		FInputSystem::OnMouseWheelDelta(GET_WHEEL_DELTA_WPARAM(wParam));
		break;

	case WM_KEYDOWN:
		FInputSystem::OnKeyDown(wParam);
		break;

	case WM_KEYUP:
		FInputSystem::OnKeyUp(wParam);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SIZE:
	{
		Width = LOWORD(lParam);
		Height = HIWORD(lParam);

		break;
	}
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

bool Window::Create(HINSTANCE hInstance, int Width, int Height, const wchar_t* Title)
{
	const wchar_t CLASS_NAME[] = L"EngineWindowClass";

	WNDCLASS wc = {};
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;
	RegisterClass(&wc);

	DWORD style = WS_OVERLAPPEDWINDOW;

	// 원하는 클라이언트 크기 -> 실제 윈도우 크기로 보정
	RECT rc = { 0, 0, Width, Height };
	AdjustWindowRect(&rc, style, FALSE);   // FALSE = 메뉴 없음
	int WindowWidth = rc.right - rc.left;
	int WindowHeight = rc.bottom - rc.top;


	hWnd = CreateWindowEx(
		0, CLASS_NAME, Title,
		style,
		CW_USEDEFAULT, CW_USEDEFAULT, WindowWidth, WindowHeight,
		nullptr, nullptr, hInstance, this);

	if (hWnd == nullptr)
		return false;

	ShowWindow(hWnd, SW_SHOW);
	return true;
}

void Window::ProcessMessage(bool& bIsRunning)
{
	MSG msg;
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (msg.message == WM_QUIT) { bIsRunning = false; }
	}
}
