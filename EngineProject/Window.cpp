#include "Window.h"
#include "Input.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		FInput::SetMouseButtonDown(EMouseButton::Left, true);
		break;
	case WM_LBUTTONUP:
		FInput::SetMouseButtonDown(EMouseButton::Left, false);
		break;
	case WM_RBUTTONDOWN:
		FInput::SetMouseButtonDown(EMouseButton::Right, true);
		break;
	case WM_RBUTTONUP:
		FInput::SetMouseButtonDown(EMouseButton::Right, false);
		break;
	case WM_MBUTTONDOWN:
		FInput::SetMouseButtonDown(EMouseButton::Middle, true);
		break;
	case WM_MBUTTONUP:
		FInput::SetMouseButtonDown(EMouseButton::Middle, false);
		break;
	case WM_XBUTTONDOWN:
	{
		int Button = GET_XBUTTON_WPARAM(wParam); // XBUTTON1 또는 XBUTTON2 매크로
		if (Button == XBUTTON1)
			FInput::SetMouseButtonDown(EMouseButton::Side1, true);
		else if (Button == XBUTTON2)
			FInput::SetMouseButtonDown(EMouseButton::Side2, true);
		break;
	}

	case WM_XBUTTONUP:
	{
		int Button = GET_XBUTTON_WPARAM(wParam); // XBUTTON1 또는 XBUTTON2 매크로
		if (Button == XBUTTON1)
			FInput::SetMouseButtonDown(EMouseButton::Side1, false);
		else if (Button == XBUTTON2)
			FInput::SetMouseButtonDown(EMouseButton::Side2, false);
		break;
	}
	
	case WM_KEYDOWN:
		FInput::SetKeyDown(wParam, true);
		break;

	case WM_KEYUP:
		FInput::SetKeyDown(wParam, false);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

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

	hWnd = CreateWindowEx(
		0, CLASS_NAME, title,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, Width, Height,
		nullptr, nullptr, hInstance, nullptr);

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
