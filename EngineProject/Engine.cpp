#include "EnginePCH.h"

#include "Engine.h"
#include "EngineStatics.h"
#include "InputSystem.h"

#include "ObjectFactory.h"

#include "Component/SceneComponent.h"

void* operator new(size_t size)
{
	void* ptr = malloc(size);
	if (!ptr)
		throw std::bad_alloc();

	FEngineStatics::TotalAllocationBytes += static_cast<uint32>(size);
	FEngineStatics::TotalAllocationCount += 1;
	return ptr;
}

void operator delete(void* ptr, size_t size)
{
	FEngineStatics::TotalAllocationBytes -= static_cast<uint32>(size);
	FEngineStatics::TotalAllocationCount -= 1;
	free(ptr);
}

bool Engine::Init(HINSTANCE hInstance)
{
	// Create Main Window
	MainWindow = MakeUnique<Window>();
	if (!MainWindow->Create(hInstance, 1280, 720, L"Engine"))
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
		MainWindow->ProcessMessage(bIsRunning);

		if (FInputSystem::IsKeyDown(EKeyCode::Escape))
		{
			bIsRunning = false;
		}

		FInputSystem::UpdateInputStates();
	}
}

void Engine::Shutdown()
{

}
