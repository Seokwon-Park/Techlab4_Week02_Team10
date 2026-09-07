#include "EnginePCH.h"

#include "CameraActor.h"
#include "Component/CameraComponent.h"

ACameraActor::ACameraActor()
{
	CameraComponent = new UCameraComponent;
	Components.push_back(CameraComponent);
}

ACameraActor::~ACameraActor()
{
	delete CameraComponent;

	for (auto& i : SceneComponents)
	{
		delete i;
	}
}

void ACameraActor::BeginPlay()
{
	Super::BeginPlay();
}

void ACameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*CameraComponent->TickComponent(DeltaTime);

	for (auto& i : SceneComponents)
	{
		i->TickComponent(DeltaTime);
	}*/
}

UCameraComponent* ACameraActor::GetCameraComponent()
{
	return CameraComponent;
}