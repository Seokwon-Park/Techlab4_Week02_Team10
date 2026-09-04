#pragma once

#include "String.h"

class UObject;

using ClassConstructor = UObject * (*)();

struct FClass 
{
	FClass();

	FString Name;
	FClass* Super = nullptr;
	ClassConstructor Constructor = nullptr;
};