#pragma once

#include "Actor.h"
#include "Component/CameraComponent.h"
	
class ACameraActor : public AActor
{
	DECLARE_CLASS(ACameraActor, AActor)
public:
	ACameraActor() = default;
protected:
	UCameraComponent* CameraComponent;
	USceneComponent* USeceneComponent;

public:
	UCameraComponent* GetCameraComponent(); // return CameraComponent subobject
	virtual USceneComponent* GetDefaultAttachComponent(); // override ? <- Need to override Actors one in UE
	virtual void BeginPlay();

};
