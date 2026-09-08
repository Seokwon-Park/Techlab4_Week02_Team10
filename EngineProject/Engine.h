#pragma once

#include "Window.h"
#include "String.h"
#include "Types.h"
#include "Containers.h"

#include "World.h"
#include "Renderer.h"
#include "ImGuiRenderer.h"
#include "Editor/GridRenderer.h"
#include "Editor/GizmoRenderer.h"

#include "Editor/EditorUI.h"
#include "Editor/ConsolePanel.h"
#include "Editor/PropertyPanel.h"
#include "Editor/ControlPanel.h"

class Engine
{
public:
	bool Init(HINSTANCE hInstance);
	void Run();
	void Shutdown();

	static FConsolePanel* GetConsolePanel() { return ConsolePanel; }

private:
	bool bIsRunning = false;
	TUniquePtr<Window> MainWindow;

	UWorld* World;

	TUniquePtr<FEditorUI> EditorUI;
	TUniquePtr<FRenderer> Renderer;
	TUniquePtr<FImGuiRenderer> ImGuiRenderer;
	TUniquePtr<FGridRenderer> GridRenderer;
	TUniquePtr<FGizmoRenderer> GizmoRenderer;
	TUniquePtr<FGizmo> Gizmo;

	inline static FConsolePanel* ConsolePanel = nullptr;
	inline static FPropertyPanel* PropertyPanel = nullptr;
	inline static FControlPanel* ControlPanel = nullptr;

	TSharedPtr<FVertexBuffer> vb;
	TSharedPtr<FIndexBuffer> ib;
	TSharedPtr<FMesh> Mesh;
	TSharedPtr<FShader> Shader;
};

