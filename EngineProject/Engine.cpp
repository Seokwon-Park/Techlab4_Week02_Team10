#include "EnginePCH.h"

#include "Engine.h"
#include "EngineStatics.h"
#include "EngineTimer.h"
#include "InputSystem.h"

#include "ObjectFactory.h"

#include "GeometryGenerator.h"

#include "World.h"

#include "Renderer.h"
#include "Picking.h"

#include "CameraActor.h"
#include "Component/CameraComponent.h"

void* operator new(uint64 Size)
{
	void* Ptr = malloc(Size);
	if (!Ptr)
		throw std::bad_alloc();

	FEngineStatics::TotalAllocationBytes += static_cast<uint64>(Size);
	FEngineStatics::TotalAllocationCount += 1;
	return Ptr;
}

void operator delete(void* Ptr, uint64 Size)
{
	FEngineStatics::TotalAllocationBytes -= static_cast<uint64>(Size);
	FEngineStatics::TotalAllocationCount -= 1;
	free(Ptr);
}

bool Engine::Init(HINSTANCE hInstance)
{
	// Create Main Window
	MainWindow = MakeUnique<Window>();
	if (!MainWindow->Create(hInstance, 1280, 720, L"Engine"))
	{
		return false;
	}

	// Create Renderer
	Renderer = MakeUnique<FRenderer>();
	Renderer->Create(MainWindow->GetHandle());

	ImGuiRenderer = MakeUnique<FImGuiRenderer>();
	ImGuiRenderer->Init(MainWindow->GetHandle(), Renderer->GetDevice(), Renderer->GetDeviceContext());

	GridRenderer = MakeUnique<FGridRenderer>();
	GridRenderer->Init(Renderer.get());

	GizmoRenderer = MakeUnique<FGizmoRenderer>();
	GizmoRenderer->Init(Renderer.get());

	EditorUI = MakeUnique<FEditorUI>();
	ConsolePanel = EditorUI->AddEditorPanel<FConsolePanel>();
	// PropertyPanel Add
	PropertyPanel = EditorUI->AddEditorPanel<FPropertyPanel>();
	ControlPanel = EditorUI->AddEditorPanel<FControlPanel>();
	EditorUI->Init();


	// Do Sth
	World = new UWorld();
	World->Init();	//return bool

	FTransform Transform;
	AActor* Actor = World->SpawnActor(AActor::StaticClass(), &Transform);
	Actor->AddPrimitiveComponent(EPrimitiveType::Cube);

	FMeshData Data = FGeometryGenerator::CreateCube(1.0f);
	//FMeshData Data = FGeometryGenerator::CreateCylinder(1.0f, 3.0f, 20, FVector4(1.0f, 0.0f, 0.0f, 1.0f));
	//FMeshData Data = FGeometryGenerator::CreateCone(1.0f, 3.0f, 20, FVector4(1.0f, 0.0f, 0.0f, 1.0f));
	//FMeshData Data = FGeometryGenerator::CreateArrow(0.1f, 1.0f, 0.2f, 0.5f, 20, FVector4(1.0f, 0.0f, 0.0f, 1.0f));
	vb = Renderer->CreateVertexBuffer(Data.Vertices.data(), sizeof(FVertex) * (UINT)Data.Vertices.size(), sizeof(FVertex));
	ib = Renderer->CreateIndexBuffer(Data.Indices.data(), Data.Indices.size());

	//TArray<FVertex> Vertices =
	//{
	//	{{0.0f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}}, // Forward=2, Right=-0.5, Up=0
	//	{{0.0f,  0.0f, 0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}}, // Forward=2, Right=0,    Up=0.5
	//	{{0.0f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}}, // Forward=2, Right=0.5,  Up=0
	//};

	//TArray<uint32> Indices = { 0,1,2 };

	//vb = Renderer->CreateVertexBuffer(Vertices.data(), sizeof(FVertex) * (UINT)Vertices.size());
	//ib = Renderer->CreateIndexBuffer(Indices.data(), sizeof(uint32) * (UINT)Indices.size());

	Mesh = MakeShared<FMesh>();
	Mesh->VertexBuffer = vb;
	Mesh->IndexBuffer = ib;

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION" , 0 , DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	Shader = Renderer->CreateShader(L"Shader/DefaultShader.hlsl", layout, 2);
	
	Actor->GetPrimitiveComponent()->SetMeshShader(Mesh, Shader);
	Actor->GetPrimitiveComponent()->SetMeshData(Data);

	PropertyPanel->transform = Actor->GetPrimitiveComponent()->GetTransform();
	ControlPanel->FControlPanel::World = World;
	ControlPanel->FControlPanel::Mesh = Mesh;
	ControlPanel->FControlPanel::Shader = Shader;
	bIsRunning = true;

	return true;
}

void Engine::Run()
{
	EngineTimer::Init();
	//World->SpawnPrimitive(UPrimitiveComponent::StaticClass());

	LOG(Info, "{}", "Hello, World!");
	World->SaveScene("A");

	FMatrix Mat;
	Mat.SetIdentity();

	while (bIsRunning)
	{
		EngineTimer::Tick();
		float DeltaTime = EngineTimer::GetDeltaTime();
		ControlPanel->FControlPanel::DeltaTime = DeltaTime;
		MainWindow->ProcessMessage(bIsRunning);
		World->Tick(DeltaTime);

		if (FInputSystem::IsKeyPressed(EKeyCode::A))
		{
			LOG(Info, "{}", "Hello, World!");
		}

		TQueue<FRenderPacket> RenderQueue;
		World->GatherRenderPackets(RenderQueue);
		FInputSystem::UpdateInputStates();

		Renderer->BeginFrame();

		Renderer->BindShader(Shader);
		FMatrix VP = World->GetMainCamera()->GetCameraComponent()->GetViewProjectionMatrix();
		//Renderer->BindBuffer(Mesh.get());
		GridRenderer->OnRender(Mat, VP);
		GizmoRenderer->OnRender(VP);

		//FTransform transform;
		//World->GetMainCamera()->GetCameraComponent()->SetTransform(FVector(-1.0f, 0.0f, 0.0f));
		//Renderer->UpdateConstantBuffer(VP);
		//Renderer->Draw(36);

		Renderer->RenderAll(RenderQueue, VP);

		ImGuiRenderer->Begin();

		ImGui::ShowDemoWindow();
		EditorUI->OnRender();

		ImGuiRenderer->End();



		Renderer->EndFrame();
	}
}

void Engine::Shutdown()
{
	Renderer->Shutdown();
}
