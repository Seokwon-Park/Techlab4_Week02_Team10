#include "EnginePCH.h"
#include "Class.h"

#include "Object.h"

FClass::FClass()
{
}

bool FClass::IsChildOf(FClass* BaseClass) const
{
	if (!BaseClass) return false;
	for (const FClass* c = this; c; c = c->Super)
	{
		if (c == BaseClass) return true;
	}
	return false;
}

UObject* FClass::GetDefaultObject() 
{
	if (!DefaultObject)
	{
		DefaultObject = Constructor();
	}
	return DefaultObject;
}


