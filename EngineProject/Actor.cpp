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
	World->AddPrimitive(Primitive);
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
		Primitive = FObjectFactory::ConstructObject<USphereComponent>();
		break;
	case EPrimitiveType::Cube:
		Primitive = FObjectFactory::ConstructObject<UCubeComponent>();
		break;
	default:
		break;
	}
	Components.push_back(Primitive);
}
