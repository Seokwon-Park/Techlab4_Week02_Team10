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

	friend class UWorld;
protected:

private:
	UWorld* World;

	USceneComponent* Root;
	TArray<UActorComponent*> Components;

	// 임시
	UPrimitiveComponent* Primitive;
};