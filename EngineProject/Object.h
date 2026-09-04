#pragma once

#include "Types.h"
#include "Containers.h"

#include "Class.h"

#define DECLARE_CLASS(ClassName, SuperClassName)                        \
public:                                                                 \
    using Super = SuperClassName;                                       \
    static FClass* StaticClass()                                        \
    {                                                                   \
        static FClass c;                                                \
        static bool bIsInit = false;                                    \
        if (!bIsInit)                                                   \
        {                                                               \
            c.Name  = #ClassName;                                       \
            c.Super = SuperClassName::StaticClass();                    \
            c.Constructor = []() -> UObject* { return new ClassName(); };\
            bIsInit = true;                                             \
        }                                                               \
        return &c;                                                      \
    }                                                                   \
    virtual FClass* GetClass() const override { return StaticClass(); }


class UObject
{
public:
	UObject();
	virtual ~UObject();

	static FClass* StaticClass()
	{
		static FClass c;
		static bool bIsInit = false;
		if (!bIsInit)
		{
			c.Name = "";
			c.Super = nullptr;
			bIsInit = true;
		}
		return &c;
	}
	virtual FClass* GetClass() const { return StaticClass(); }

	template <typename T>
	bool IsA()
	{
		return IsA(T::StaticClass());
	}

	bool IsA(FClass* Class);
	

private:
	uint32 UUID;
	uint32 InternalIndex;
};

extern TArray<UObject*> GUObjectArray;
