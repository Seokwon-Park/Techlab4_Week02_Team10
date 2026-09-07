#pragma once

#include "Object.h"
#include "Actor.h"
#include "Component/PrimitiveComponent.h"
#include "Transform.h"
#include "Renderer.h"

class ACameraActor;

class UWorld : public UObject
{
public:
	virtual ~UWorld();

	bool Init();
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

	inline void AddPrimitive(UPrimitiveComponent* Primitive) { PrimitiveComponents.push_back(Primitive); }

	void GatherRenderPackets(TQueue<FRenderPacket>& RenderQueue);
	UPrimitiveComponent* GetPickingPrimitive();

	// 카메라 세터, 게터
	void SetMainCamera(ACameraActor* Camera);
	ACameraActor* GetMainCamera() const;

private:
	TArray<AActor*> Actors;

	TQueue<AActor*> BeginPlayList;
	
	TArray<UPrimitiveComponent*> PrimitiveComponents;

	//카메라 추가 
	ACameraActor* MainCamera = nullptr;
};
