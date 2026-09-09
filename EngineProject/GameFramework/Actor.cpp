#include "EnginePCH.h"
#include "Actor.h"

#include "../ObjectSystem/ObjectFactory.h"
#include "../Engine/World.h"

#include "../Component/CubeComponent.h"
#include "../Component/SphereComponent.h"

AActor::AActor()
{
	
}

void AActor::BeginPlay()
{
	if (UPrimitiveComponent* Primitive = Cast<UPrimitiveComponent>(Root))
	{
		World->AddPrimitive(Cast<UPrimitiveComponent>(Root));

	}

	for (UActorComponent* Component : Components)
	{
		Component->BeginPlay();
	}

}

void AActor::Tick(float DeltaTime)
{
	for (UActorComponent* Component : Components)
	{
		Component->TickComponent(DeltaTime);
	}
}

void AActor::AddPrimitiveComponent(EPrimitiveType Type)
{
	switch (Type)
	{
	case EPrimitiveType::Sphere:
		Root = FObjectFactory::ConstructObject<USphereComponent>();
		break;
	case EPrimitiveType::Cube:
		Root = FObjectFactory::ConstructObject<UCubeComponent>();
		break;
	default:
		break;
	}
	Components.push_back(Root);
}

void AActor::SetRootComponent(USceneComponent* SceneComponent)
{
	Root = SceneComponent;
}

USceneComponent* AActor::GetRootComponent()
{
	return Root;
}