#pragma once

#include "Window.h"
#include "String.h"
#include "Types.h"
#include "Containers.h"

#include "World.h"
#include "Renderer.h"

class Engine
{
public:
	bool Init(HINSTANCE hInstance);
	void Run();
	void Shutdown();

private:
	bool bIsRunning = false;
	TUniquePtr<Window> MainWindow;

	UWorld* World;
	
	TUniquePtr<FRenderer> Renderer;
};

