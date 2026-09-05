#pragma once

#include "SceneComponent.h"

enum class EPrimitiveType
{
	Sphere,
	Cube
};

class UPrimitiveComponent :public USceneComponent
{
	DECLARE_CLASS(UPrimitiveComponent, USceneComponent)

	REFLECT_START(ClassName)
		REFLECT_END()
public:
	void Render();

	EPrimitiveType GetType() const { return Type; }
private:
	EPrimitiveType Type;

};