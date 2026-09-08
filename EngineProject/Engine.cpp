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
#include "ResourceManager.h"

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

	Gizmo = MakeUnique<FGizmo>();

	EditorUI = MakeUnique<FEditorUI>();
	ConsolePanel = EditorUI->AddEditorPanel<FConsolePanel>();
	// PropertyPanel Add
	PropertyPanel = EditorUI->AddEditorPanel<FPropertyPanel>();
	ControlPanel = EditorUI->AddEditorPanel<FControlPanel>();
	EditorUI->Init();

	// Resource Manager 
	FResourceManager::GetInstance().Init(Renderer.get());

	// OutLine
	OutlineRenderer = MakeUnique<FOutlineRenderer>();
	OutlineRenderer->Init(Renderer.get());

	Outline = MakeUnique<FOutline>();


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

	Actor->GetPrimitiveComponent()->SetMeshShader(Mesh, Shader.get());
	Actor->GetPrimitiveComponent()->SetMeshData(Data);

	PropertyPanel->transform = Actor->GetPrimitiveComponent()->GetTransform();
	ControlPanel->FControlPanel::World = World;
	ControlPanel->FControlPanel::Mesh = Mesh;
	ControlPanel->FControlPanel::Shader = Shader.get();
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

	UPrimitiveComponent* OutlineComponent = nullptr;

	while (bIsRunning)
	{
		EngineTimer::Tick();
		float DeltaTime = EngineTimer::GetDeltaTime();
		ControlPanel->FControlPanel::DeltaTime = DeltaTime;
		MainWindow->ProcessMessage(bIsRunning);
		World->Tick(DeltaTime);

		FMatrix VP = World->GetMainCamera()->GetCameraComponent()->GetViewProjectionMatrix();

		FRay ray = World->GetMainCamera()->GetCameraComponent()->DeProjection(FInputSystem::GetMouseX(), FInputSystem::GetMouseY());
		FVector2 mousePos(FInputSystem::GetMouseX(), FInputSystem::GetMouseY());
		bool bMouseDown = FInputSystem::IsMouseDown(EMouseButton::Left);

		Gizmo->Update(ray, mousePos, VP, 1280, 720, bMouseDown);

		
		if (FInputSystem::IsMousePressed(EMouseButton::Left) && !Gizmo->IsUsing() && Gizmo->GetHoveredAxis() < 0 && !ImGui::GetIO().WantCaptureMouse)
		{
			UPrimitiveComponent* PickedComponent = World->GetPickingPrimitive();
			OutlineComponent = PickedComponent;
			Gizmo->SetTarget(PickedComponent);
			Outline->SetTarget(OutlineComponent);
		}

		if (FInputSystem::IsKeyPressed(EKeyCode::Space))
		{
			static int ModeIndex = 0;
			ModeIndex = (ModeIndex + 1) % 3;
			Gizmo->SetMode(static_cast<EGizmoMode>(ModeIndex));
		}

		TQueue<FRenderPacket> RenderQueue;
		World->GatherRenderPackets(RenderQueue);
		FInputSystem::UpdateInputStates();

		Renderer->BeginFrame();

		Renderer->BindShader(Shader.get());

		//Renderer->BindBuffer(Mesh.get());
		GridRenderer->OnRender(Mat, VP);
		if (Gizmo->GetTarget())
			GizmoRenderer->OnRender(*Gizmo, VP);

		//FTransform transform;
		//World->GetMainCamera()->GetCameraComponent()->SetTransform(FVector(-1.0f, 0.0f, 0.0f));
		//Renderer->UpdateConstantBuffer(VP);
		//Renderer->Draw(36);

		//Renderer->RenderAll(RenderQueue, VP);

		//if (Outline->GetTarget())
			OutlineRenderer->OnRender(*Outline, VP);

		ImGuiRenderer->Begin();

		ImGui::ShowDemoWindow();
		EditorUI->OnRender();

		

		ImGuiRenderer->End();



		Renderer->EndFrame();
	}
}

void Engine::Shutdown()
{
	delete World;
	Renderer->Shutdown();
}
