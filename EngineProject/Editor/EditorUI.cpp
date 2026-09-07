#include "EnginePCH.h"
#include "EditorUI.h"

bool FEditorUI::Init()
{
	return true;
}

void FEditorUI::OnRender()
{
	for (auto& Panel : Panels)
	{
		Panel->OnRender();
	}
}
