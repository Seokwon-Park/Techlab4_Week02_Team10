#include "EnginePCH.h"
#include "Actor.h"

#include "ObjectFactory.h"
#include "World.h"

#include "Component/CubeComponent.h"
#include "Component/SphereComponent.h"

AActor::AActor()
{
	
}

void AActor::BeginPlay()
{
	World->AddPrimitive(Cast<UPrimitiveComponent>(Root));
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

USceneComponent* AActor::GetRootComponent()
{
	return Root;
}