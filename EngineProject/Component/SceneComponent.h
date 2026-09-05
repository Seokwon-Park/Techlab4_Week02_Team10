#pragma once

#include "../Transform.h"
#include "ActorComponent.h"

class USceneComponent :public UActorComponent
{
	DECLARE_CLASS(USceneComponent, UObject)
public:
private:
	FTransform transform;
	
};