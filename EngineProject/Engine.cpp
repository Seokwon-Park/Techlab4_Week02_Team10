#include "EnginePCH.h"

#include "Engine.h"
#include "EngineStatics.h"
#include "EngineTimer.h"
#include "InputSystem.h"

#include "ObjectFactory.h"

#include "Component/SceneComponent.h"
#include "World.h"

#include "Picking.h"

void* operator new(uint64 Size)
{
	void* Ptr = malloc(Size);
	if (!Ptr)
		throw std::bad_alloc();

	FEngineStatics::TotalAllocationBytes += static_cast<uint64>(Size);
	FEngineStatics::TotalAllocationCount += 1;
	return Ptr;
}

void operator delete(void* Ptr, uint64 Size)
{
	FEngineStatics::TotalAllocationBytes -= static_cast<uint64>(Size);
	FEngineStatics::TotalAllocationCount -= 1;
	free(Ptr);
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
	World = new UWorld();

	bIsRunning = true;

	return true;
}

void Engine::Run()
{
	EngineTimer::Init();

	//World->SpawnPrimitive(UPrimitiveComponent::StaticClass());
	World->SaveScene("A");
	while (bIsRunning)
	{
		EngineTimer::Tick();
		float DeltaTime = EngineTimer::GetDeltaTime();

		MainWindow->ProcessMessage(bIsRunning);

		World->Tick(DeltaTime);

		FInputSystem::UpdateInputStates();
	}
}

void Engine::Shutdown()
{
	
}
