#include "EnginePCH.h"
#include "Actor.h"

#include "../ObjectSystem/ObjectFactory.h"
#include "../Engine/World.h"

#include "../Component/CubeComponent.h"
#include "../Component/SphereComponent.h"
#include "../Engine/ResourceManager.h"

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
	case EPrimitiveType::Cone:
		Root = FObjectFactory::ConstructObject<UPrimitiveComponent>();
		Cast<UPrimitiveComponent>(Root)->SetMesh(FResourceManager::GetInstance().GetMesh("Cone"));
		Cast<UPrimitiveComponent>(Root)->SetMeshData(FGeometryGenerator::GetMeshData("Cone"));
		Cast<UPrimitiveComponent>(Root)->SetType(Type);
	case EPrimitiveType::Plane:
		Root = FObjectFactory::ConstructObject<UPrimitiveComponent>();
		Cast<UPrimitiveComponent>(Root)->SetMesh(FResourceManager::GetInstance().GetMesh("Plane"));
		Cast<UPrimitiveComponent>(Root)->SetMeshData(FGeometryGenerator::GetMeshData("Plane"));
		Cast<UPrimitiveComponent>(Root)->SetType(Type);
	default:
		break;
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