#pragma once

#include "Object.h"
#include "Actor.h"
#include "Component/PrimitiveComponent.h"
#include "Transform.h"
#include "Renderer.h"


class UWorld : public UObject
{
public:
	virtual ~UWorld();

	/*UPrimitiveComponent* SpawnPrimitive(FClass* Class);*/
	AActor* SpawnActor(FClass* Class, const FTransform* Transform);

	template <class T>
	T* SpawnActor(const FTransform* Transform)
	{
		return CastChecked<T>(SpawnActor(T::StaticClass(), Transform));
	}

	void Tick(float DeltaTime);

	void OnRender(FRenderer* Renderer);

	bool SaveScene(const FString& Path);
	bool LoadScene(const FString& Path);

	inline void AddPrimitive(UPrimitiveComponent* Primitive) { Primitives.push_back(Primitive); }
private:
	TArray<AActor*> Actors;

	TQueue<AActor*> BeginPlayList;
	
	void GatherRenderPackets(TQueue<FRenderPacket>& RenderQueue);
	TArray<UPrimitiveComponent*> PrimitiveComponents;
};
