#pragma once

#include "../Object.h"

class UActorComponent : public UObject
{
	DECLARE_CLASS(UActorComponent, UObject)
public:
	virtual void BeginPlay();
	virtual void TickComponent(float DeltaTime);
private:

};