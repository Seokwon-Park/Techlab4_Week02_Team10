#include "Object.h"

#include "EngineStatics.h"

UObject::UObject()
{
	UUID = FEngineStatics::GetUUID();
	InternalIndex = GUObjectArray.size();
	GUObjectArray.push_back(this);
}

UObject::~UObject()
{
}
