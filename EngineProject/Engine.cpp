#include "Engine.h"

bool Engine::Init(HINSTANCE hInstance)
{
	// Create Main Window
	mainWindow = MakeUnique<Window>();
	if (!mainWindow->Create(hInstance, 1280, 720, L"Engine"))
	{
		return false;
	}

	// Do Sth

	bIsRunning = true;

	return true;
}

void Engine::Run()
{
	while (bIsRunning)
	{
		mainWindow->ProcessMessage(bIsRunning);
	}
}

void Engine::Shutdown()
{

}
