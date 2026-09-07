#pragma once

#include <Windows.h>

class Window
{
public:
	bool Create(HINSTANCE hInstance, int width, int height, const wchar_t* title);
	void ProcessMessage(bool& bIsRunning);

	HWND GetHandle() const { return hWnd;  }
private:
	HWND hWnd = nullptr;
};