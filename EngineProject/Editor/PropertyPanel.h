#pragma once

#include "EditorPanel.h"

class PropertyPanel : public IEditorPanel
{
private:
	bool Init() override;
	void OnRender() override;
};