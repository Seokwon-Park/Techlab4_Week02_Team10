#pragma once

#include <Windows.h>

// 윈도우 사이즈
extern uint32 Width;
extern uint32 Height;

class Window
{
public:
	bool Create(HINSTANCE hInstance, int width, int height, const wchar_t* title);
	void ProcessMessage(bool& bIsRunning);

	HWND GetHandle() const { return hWnd;  }

	uint32 GetWidth() const { return Width; }
	uint32 GetHeight() const { return Height; }
private:
	HWND hWnd = nullptr;
 };

