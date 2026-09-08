#include "EnginePCH.h"
#include "SphereComponent.h"
#include "ResourceManager.h"

void USphereComponent::BeginPlay()
{
	Super::BeginPlay();
	SetMeshData(FResourceManager::GetInstance().GetMesh("Sphere"));
}
