#pragma once

#include "String.h"
#include "Property.h"

class UObject;

using ClassConstructor = UObject * (*)();

struct FClass 
{
	FClass();

	FString Name;
	FClass* Super = nullptr;
	ClassConstructor Constructor = nullptr;

	TArray<FProperty> Properties;
	UObject* DefaultObject = nullptr;

	bool IsChildOf(FClass* BaseClass) const;
};