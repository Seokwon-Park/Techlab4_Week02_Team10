#pragma once

#include "Object.h"
#include "Actor.h"
#include "Component/PrimitiveComponent.h"
#include "Transform.h"


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

	bool SaveScene(const FString& Path);
	bool LoadScene(const FString& Path);
private:
	TArray<AActor*> Actors;
	
};
