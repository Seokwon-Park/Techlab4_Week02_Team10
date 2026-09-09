#pragma once

#include "Core/Types.h"
#include "Core/Containers.h"

class UClass;
// Property Reflection

#define REFLECT_START(ClassName) \
public: \
	inline static void RegisterProperties(UClass* InClass) \
	{

#define PROPERTY(PropertyName) \
    InClass->AddProperty<decltype(ThisClass::PropertyName)>(#PropertyName, offsetof(ThisClass, PropertyName));

#define REFLECT_END()\
	};\
private:

#define DECLARE_CLASS(ClassName, SuperClassName)                        \
public:                                                                 \
    using Super = SuperClassName;                                       \
    using ThisClass = ClassName;		                                \
    static UClass* StaticClass()                                        \
    {                                                                   \
        static UClass c;                                                \
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
    virtual UClass* GetClass() const override { return StaticClass(); } \
private:																

class UObject
{
public:
	UObject();
	virtual ~UObject();

	static UClass* StaticClass();
	virtual UClass* GetClass() const;

	template <typename T>
	bool IsA()
	{
		return IsA(T::StaticClass());
	}

	bool IsA(UClass* Class);

	uint32 GetUUID() const { return UUID; }
	void SetUUID(uint32 Uid) { UUID = Uid; }

	inline static void RegisterProperties(UClass* InClass) {};

private:
	uint32 UUID;
	uint32 InternalIndex;
};

extern TArray<UObject*> GUObjectArray;
