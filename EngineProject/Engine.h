#pragma once

#include "Window.h"
#include "String.h"
#include "Types.h"
#include "Containers.h"

class Engine
{
public:
	bool Init(HINSTANCE hInstance);
	void Run();
	void Shutdown();

private:
	bool bIsRunning = false;
	TUniquePtr<Window> mainWindow;
};

