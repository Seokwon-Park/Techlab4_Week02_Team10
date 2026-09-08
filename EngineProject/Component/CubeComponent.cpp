#include "EnginePCH.h"
#include "CubeComponent.h"
#include "../ResourceManager.h"

void UCubeComponent::BeginPlay()
{
	Super::BeginPlay();
	SetMeshData(FResourceManager::GetInstance().GetMesh("Cube"));
}
