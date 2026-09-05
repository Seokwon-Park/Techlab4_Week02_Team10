#pragma once

#include "Object.h"
#include "Component/SceneComponent.h"

class AActor : public UObject
{
	DECLARE_CLASS(AActor, UObject)
public:
	AActor() = default;
	virtual ~AActor() = default;

	virtual void BeginPlay() {};
	virtual void Tick(float DeltaTime) {};
protected:


private:
	USceneComponent* Root;
	TArray<UActorComponent*> Components;
};