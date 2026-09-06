#include "EnginePCH.h"
#include "Actor.h"

#include "ObjectFactory.h"
#include "World.h"

AActor::AActor()
{
	Primitive = FObjectFactory::ConstructObject<UPrimitiveComponent>();
}

void AActor::BeginPlay()
{
	World->AddPrimitive(Primitive);
}

void AActor::Tick(float DeltaTime)
{
}
