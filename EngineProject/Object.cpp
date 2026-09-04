#include "EnginePCH.h"
#include "Object.h"

#include "EngineStatics.h"

TArray<UObject*> GUObjectArray;

UObject::UObject()
{
	UUID = FEngineStatics::GetUUID();
	InternalIndex = GUObjectArray.size();
	GUObjectArray.push_back(this);
}

UObject::~UObject()
{
}

