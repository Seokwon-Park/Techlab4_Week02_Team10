#pragma once

#include "../Transform.h"
#include "ActorComponent.h"

class USceneComponent :public UActorComponent
{
	DECLARE_CLASS(USceneComponent, UActorComponent)

	REFLECT_START(ClassName)
		PROPERTY(bVisible)
	REFLECT_END()
public:
	FTransform* GetTransform();
	FMatrix GetWorldMatrix() const;
private:
	//FTransform transform;
	bool bVisible = true;
protected:
	// Protected로 이동
	FTransform transform;
};