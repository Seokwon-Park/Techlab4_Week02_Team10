#include "EnginePCH.h"
#include "ObjectFactory.h"

UObject* FObjectFactory::ConstructObject(FClass* Class)
{
    if (!Class || !Class->Constructor)
        return nullptr;
    return Class->Constructor();
}
