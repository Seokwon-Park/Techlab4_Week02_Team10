#pragma once

#include "Object.h"
#include "Component/PrimitiveComponent.h"

class UWorld;


class AActor : public UObject
{
	DECLARE_CLASS(AActor, UObject)

	REFLECT_START(ClassName)
		REFLECT_END()
public:
	AActor();
	virtual ~AActor() = default;

	virtual void BeginPlay();
	virtual void Tick(float DeltaTime);

	UWorld* GetWorld() const { return World; }

	UPrimitiveComponent* GetPrimitiveComponent() const { return Cast<UPrimitiveComponent>(Root); }
	void AddPrimitiveComponent(EPrimitiveType Type);

	USceneComponent* GetRootComponent();

	friend class UWorld;
protected:
	TArray<UActorComponent*> Components;

private:
	UWorld* World = nullptr;

	USceneComponent* Root = nullptr;

	// 임시
	//UPrimitiveComponent* Primitive = nullptr;
};