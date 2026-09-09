#include "EnginePCH.h"
#include "Actor.h"

#include "ObjectFactory.h"
#include "World.h"

#include "Component/CubeComponent.h"
#include "Component/SphereComponent.h"

AActor::AActor()
{
	
}

AActor::~AActor()
{
	Root = nullptr;
	Components.clear();
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

void AActor::AddPrimitiveComponent(EPrimitiveType Type, FTransform Transform)
{
	switch (Type)
	{
	case EPrimitiveType::Sphere:
		Root = FObjectFactory::ConstructObject<USphereComponent>();
		Cast<UPrimitiveComponent>(Root)->SetType(Type);
		break;
	case EPrimitiveType::Cube:
		Root = FObjectFactory::ConstructObject<UCubeComponent>();
		Cast<UPrimitiveComponent>(Root)->SetType(Type);
		break;
	default:
		break;
	}
	Root->SetTransform(Transform);
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