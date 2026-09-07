#pragma once

#include "Window.h"
#include "String.h"
#include "Types.h"
#include "Containers.h"

#include "World.h"
#include "Renderer.h"
#include "ImGuiRenderer.h"

#include "Editor/EditorUI.h"
#include "Editor/ConsolePanel.h"

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

	inline static FConsolePanel* ConsolePanel = nullptr;

	ID3D11Buffer* vb;
	ID3D11Buffer* ib;
	FShader* Shader;
	TSharedPtr<FMesh> Mesh;
};

