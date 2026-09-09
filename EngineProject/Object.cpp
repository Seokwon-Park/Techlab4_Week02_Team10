#include "EnginePCH.h"
#include "Object.h"

#include "EngineStatics.h"
#include "Class.h"

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

UClass* UObject::StaticClass()
{
	static UClass c;
	static bool bIsInit = false;
	if (!bIsInit)
	{
		c.Name = "Object";
		c.Super = nullptr;
		c.Constructor = []() -> UObject*
			{
				return new UObject();
			};
		bIsInit = true;
	}
	return &c;
}

UClass* UObject::GetClass() const
{
	return StaticClass();
}

bool UObject::IsA(UClass* Class)
{
	return GetClass()->IsChildOf(Class);
}

