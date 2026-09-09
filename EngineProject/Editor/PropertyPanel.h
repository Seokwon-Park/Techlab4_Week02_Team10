#pragma once

#include <format>
#include "EditorPanel.h"

struct FTransform;

class FPropertyPanel : public IEditorPanel
{
public:
	bool Init() override;
	void OnRender() override;
	FPropertyPanel() = default;
	~FPropertyPanel();

	UWorld* World;
	TSharedPtr<FGizmo> Gizmo;

	int32 GizmoSelectedIndex = 0;

	const char* GizmoItems[3] =
	{
		"Location",
		"Rotation",
		"Scale"
	};

	int32 SpaceSelectedIndex = 0;

	const char* SpaceItems[2] =
	{
		"Local",
		"World"
	};

};

