#pragma once

#include "EngineString.h"

enum class EPropertyType { Float, Int, Bool, Vector };

struct FProperty
{
    FString Name;
    EPropertyType Type;
    size_t Offset;
    size_t Size;
};