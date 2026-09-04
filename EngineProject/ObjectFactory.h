#pragma once

#include "Object.h"

class FObjectFactory
{
public:
	static UObject ConstructObject(FClass* Class);
private:

};