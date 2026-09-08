#pragma once
#include <format>
#include "EditorPanel.h"

class FControlPanel : public IEditorPanel
{
public:
	bool Init() override;
	void OnRender() override;

	float* FPS;
	UWorld* World; // SpawnActor MainCamera

	TSharedPtr<FMesh> Mesh;
	FShader* Shader;
	
	void AddActor(EPrimitiveType Type);
	
	int32 SelectedIndex = 0;
	int32 ActorNum = 0;

	const char* Items[3] =
	{
		"None",
		"Sphere",
		"Cube"
	};


};

