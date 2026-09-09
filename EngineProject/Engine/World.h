#pragma once

#include "ObjectSystem/Object.h"
#include "GameFramework/Actor.h"
#include "Component/PrimitiveComponent.h"
#include "Math/Transform.h"
#include "Render/Renderer.h"

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

	void ClearScene();
	bool NewScene(const FString& Path);
	bool SaveScene(const FString& Path);
	bool LoadScene(const FString& Path);

	inline void AddPrimitive(UPrimitiveComponent* Primitive) { PrimitiveComponents.push_back(Primitive); }

	void GatherRenderPackets(TQueue<FRenderPacket>& RenderQueue);
	UPrimitiveComponent* GetPickingPrimitive(uint32 ScreenW, uint32 ScreenH);

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
