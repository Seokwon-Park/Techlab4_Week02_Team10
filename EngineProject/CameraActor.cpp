#include "EnginePCH.h"

#include "CameraActor.h"

ACameraActor::ACameraActor()
{

}

ACameraActor::~ACameraActor()
{
	for (auto& i : SceneComponents)
	{
		delete i;
	}
}

void ACameraActor::BeginPlay()
{
	AddCameraComponent();
}

void ACameraActor::Tick(float DeltaTime)
{
	/*CameraComponent->TickComponent(DeltaTime);

	for (auto& i : SceneComponents)
	{
		i->TickComponent(DeltaTime);
	}*/
}

void ACameraActor::AddCameraComponent()
{
	UCameraComponent* Cam = new UCameraComponent;
	CameraComponent = Cam;
}

UCameraComponent* ACameraActor::GetCameraComponent(int i)
{
	return CameraComponent;
}