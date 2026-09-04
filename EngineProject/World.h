#pragma once

#include "Object.h"
#include "Component/PrimitiveComponent.h"
#include "json.hpp"

using json = nlohmann::ordered_json;

class UWorld : public UObject
{
public:
	UPrimitiveComponent* SpawnPrimitive(FClass* Class);

	void Tick(float DeltaTime);

	bool SaveScene(const FString& Path);
	bool LoadScene(const FString& Path);
private:
	TArray<UPrimitiveComponent*> Primitives;
};
