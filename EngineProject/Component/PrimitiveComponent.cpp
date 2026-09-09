#include "EnginePCH.h"
#include "PrimitiveComponent.h"
#include "../Renderer.h"
#include "../ResourceManager.h"

void UPrimitiveComponent::BeginPlay()
{
	Super::BeginPlay();
	Shader = FResourceManager::GetInstance().GetShader("Shader/DefaultShader.hlsl");
}

void UPrimitiveComponent::SubmitToRenderQueue(TQueue<FRenderPacket>& RenderQueue)
{
	if (Mesh && Shader)
	{
		FRenderPacket rp;
		rp.mesh = Mesh.get();
		rp.shader = Shader;
		rp.model = GetWorldMatrix();
		RenderQueue.push(rp);
	}
}

void UPrimitiveComponent::SetMesh(FMesh* InMesh)
{
	Mesh = TSharedPtr<FMesh>(InMesh);
}
