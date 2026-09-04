#pragma once

#include "Object.h"

class FObjectFactory
{
public:
	static UObject* ConstructObject(FClass* Class);

	template <typename T>
	static T* ConstructObject()
	{
		UObject* Object = ConstructObject(T::StaticClass());
		return static_cast<T*>(Object);
	}
private:

};