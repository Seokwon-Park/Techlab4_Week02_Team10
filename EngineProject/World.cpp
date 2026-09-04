#include "EnginePCH.h"
#include "World.h"

#include "ObjectFactory.h"
#include "EngineStatics.h"

namespace
{
	FString PrimitiveTypeToString(EPrimitiveType Type)
	{
		switch (Type)
		{
		case EPrimitiveType::Sphere:
			return "Sphere";
			break;
		case EPrimitiveType::Cube:
			return "Cube";
			break;
		default:
			break;
		}
	}
}

UPrimitiveComponent* UWorld::SpawnPrimitive(FClass* Class)
{
	UPrimitiveComponent* Component = FObjectFactory::ConstructObject<UPrimitiveComponent>();
	Primitives.push_back(Component);
	return Component;
}

void UWorld::Tick(float DeltaTime)
{
}

bool UWorld::SaveScene(const FString& Path)
{
	std::ifstream file(Path);
	//if (!file.is_open())
	//	return false;

	json Json;
	Json.dump(4);
	Json["Version"] = 1;
	Json["NextUUID"] = FEngineStatics::NextUUID;
	Json["Primitives"] = json::object();

	for (UPrimitiveComponent* p : Primitives)
	{
		json pJson;
		//pJson["Location"] = { p->Transform.Location.x, p->Transform.Location.y, p->Transform.Location.z };
		//pJson["Rotation"] = { p->Transform.Rotation.x, p->Transform.Rotation.y, p->Transform.Rotation.z };
		//pJson["Scale"] = { p->Transform.Scale.x,    p->Transform.Scale.y,    p->Transform.Scale.z };
		pJson["Type"] = PrimitiveTypeToString(p->GetType());

		Json["Primitives"][std::to_string(p->GetUUID())] = pJson;

	}
	std::cout << Json.dump(4);

	return true;
}

bool UWorld::LoadScene(const FString& Path)
{
	return false;
}
