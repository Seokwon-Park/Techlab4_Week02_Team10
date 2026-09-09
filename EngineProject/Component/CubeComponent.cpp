#include "EnginePCH.h"
#include "CubeComponent.h"
#include "../ResourceManager.h"

void UCubeComponent::BeginPlay()
{
	Super::BeginPlay();
	SetMesh(FResourceManager::GetInstance().GetMesh("Cube"));
	SetMeshData(FGeometryGenerator::GetMeshData("Cube"));
}
