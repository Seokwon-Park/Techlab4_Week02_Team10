#pragma once

#include "Types.h"
#include "Containers.h"

#include "Class.h"

// Property Reflection

#define REFLECT_START(ClassName) \
private: \
	inline static void RegisterProperties(FClass* InClass) \
	{

#define PROPERTY(PropertyName) \
    InClass->AddProperty<decltype(ThisClass::PropertyName)>(#PropertyName, offsetof(ThisClass, PropertyName));

#define REFLECT_END()\
	}\
private:

#define DECLARE_CLASS(ClassName, SuperClassName)                        \
public:                                                                 \
    using Super = SuperClassName;                                       \
    using ThisClass = ClassName;		                                \
    static FClass* StaticClass()                                        \
    {                                                                   \
        static FClass c;                                                \
        static bool bIsInit = false;                                    \
        if (!bIsInit)                                                   \
        {                                                               \
            c.Name  = #ClassName;                                       \
            c.Super = Super::StaticClass();								\
            c.Constructor = []() -> UObject* { return new ClassName(); };\
			ClassName::RegisterProperties(&c);							\
            bIsInit = true;                                             \
        }                                                               \
        return &c;                                                      \
    }                                                                   \
    virtual FClass* GetClass() const override { return StaticClass(); } \
private:																

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
	virtual FClass* GetClass() const { return StaticClass(); }

	template <typename T>
	bool IsA()
	{
		return IsA(T::StaticClass());
	}

	bool IsA(FClass* Class);

	uint32 GetUUID() const { return UUID; }

	inline static void RegisterProperties(FClass* InClass) {};

private:
	uint32 UUID;
	uint32 InternalIndex;
};

extern TArray<UObject*> GUObjectArray;
