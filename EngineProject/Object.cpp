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

bool UObject::IsA(FClass* Class)
{
	if (!Class) return false;
	for (FClass* c = GetClass(); c; c = c->Super)
		if (c == Class) return true;
	return false;
}

