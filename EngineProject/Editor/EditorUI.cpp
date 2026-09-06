#include "EnginePCH.h"
#include "EditorUI.h"

bool FEditorUI::Init()
{
	return false;
}

void FEditorUI::OnRender()
{
	for (auto& Panel : Panels)
	{
		Panel->OnRender();
	}
}
