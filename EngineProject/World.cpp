#include "EnginePCH.h"
#include "World.h"

#include "ObjectFactory.h"
#include "EngineStatics.h"

#include "CameraActor.h"

#include "Ray.h"

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
			return "";
			break;
		}
	}
}

//UPrimitiveComponent* UWorld::SpawnPrimitive(FClass* Class)
//{
//	UPrimitiveComponent* Component = FObjectFactory::ConstructObject<UPrimitiveComponent>();
//	Primitives.push_back(Component);
//	return Component;
//}

UWorld::~UWorld()
{
	for (AActor* Actor : Actors)
	{
		delete Actor;
	}
	Actors.clear();
}

bool UWorld::Init()
{
	// Spawn Actor로 카메라 생성하고 세팅하기
	ACameraActor* GetCamera = SpawnActor<ACameraActor>(nullptr);
	if (GetCamera)
	{
		SetMainCamera(GetCamera);
		return true;
	}
	return false;
}

AActor* UWorld::SpawnActor(FClass* Class, const FTransform* UserTransformPtr)
{
	if (!Class) return nullptr;
	if (!Class->IsChildOf(AActor::StaticClass())) return nullptr;
	const FTransform UserTransform = UserTransformPtr ? *UserTransformPtr : FTransform::Identity;
	AActor* NewActor = Cast<AActor>(FObjectFactory::ConstructObject(Class));
	NewActor->World = this;
	if (!NewActor) return nullptr;
	//TODO :
	//NewActor->...
	Actors.push_back(NewActor);
	BeginPlayList.push(NewActor);
	return NewActor;
}

void UWorld::Tick(float DeltaTime)
{
	while (!BeginPlayList.empty())
	{
		BeginPlayList.front()->BeginPlay();
		BeginPlayList.pop();
	}

	for (AActor* Actor : Actors)
	{
		Actor->Tick(DeltaTime);
	}
}

void UWorld::OnRender(FRenderer* Renderer)
{
	// Rendering
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

	//for (UPrimitiveComponent* p : Primitives)
	{
		json pJson;
		//pJson["Location"] = { p->Transform.Location.x, p->Transform.Location.y, p->Transform.Location.z };
		//pJson["Rotation"] = { p->Transform.Rotation.x, p->Transform.Rotation.y, p->Transform.Rotation.z };
		//pJson["Scale"] = { p->Transform.Scale.x,    p->Transform.Scale.y,    p->Transform.Scale.z };
		//pJson["Type"] = PrimitiveTypeToString(p->GetType());

		//Json["Primitives"][std::to_string(p->GetUUID())] = pJson;

	}
	std::cout << Json.dump(4);

	return true;
}

bool UWorld::LoadScene(const FString& Path)
{
	return false;
}

void UWorld::GatherRenderPackets(TQueue<FRenderPacket>& RenderQueue)
{
	for (UPrimitiveComponent* Primitive : PrimitiveComponents)
	{
		if (Primitive)
			Primitive->SubmitToRenderQueue(RenderQueue);
	}
}

UPrimitiveComponent* UWorld::GetPickingPrimitive()
{
	//MainCamera->
	FRay ray; // = MainCamera->Deprojection();
	float minT{ FLT_MAX };
	UPrimitiveComponent* PickingPrimitive = nullptr;

	for (UPrimitiveComponent* Primitive : PrimitiveComponents)
	{
		// ray를 로컬공간으로
		FMatrix invWorld = Primitive->GetWorldMatrix().Inverse();
		FVector4 LocalRayOrigin = invWorld.TransformPosition(ray.Origin);
		FVector4 LocalRayDir = invWorld.TransformVector(ray.Direction);

		FRay LocalRay{};
		LocalRay.Origin.X = LocalRayOrigin.X;
		LocalRay.Origin.Y = LocalRayOrigin.Y;
		LocalRay.Origin.Z = LocalRayOrigin.Z;

		LocalRay.Direction.X = LocalRayDir.X;
		LocalRay.Direction.Y = LocalRayDir.Y;
		LocalRay.Direction.Z = LocalRayDir.Z;

		const FMeshData& mesh = Primitive->GetMeshData();

		FVector BoxMin, BoxMax;
		mesh.GetAABB(BoxMin, BoxMax);
		float rayT{};

		if (!RayIntersectsAABB(LocalRay, BoxMin, BoxMax, rayT))
		{	
			continue;
		}

		if (rayT > minT)
		{
			continue;
		}

		// Broad Phase 통과하면 뮐러-트럼보르 알고리즘 수행
		for (uint32 i = 0; i + 2 < mesh.Indices.size(); i += 3)
		{
			FVector vertices[3]{};	// 3 vertex
			for (uint32 j = 0; j < 3; ++j)
			{
				uint32 index = mesh.Indices[i + j];

				vertices[j].X = mesh.Vertices[index].Position.X;
				vertices[j].Y = mesh.Vertices[index].Position.Y;
				vertices[j].Z = mesh.Vertices[index].Position.Z;
			}

			if (!RayIntersectsTriangle(LocalRay, vertices[0], vertices[1], vertices[2], rayT))
			{
				continue;
			}

			if (rayT < minT)
			{
				PickingPrimitive = Primitive;
				minT = rayT;
			}
		}
	}

	return PickingPrimitive;
}


// 카메라 관련 추가

void UWorld::SetMainCamera(ACameraActor* Camera)
{
	MainCamera = Camera;
}

ACameraActor* UWorld::GetMainCamera() const
{
	return MainCamera;
}
