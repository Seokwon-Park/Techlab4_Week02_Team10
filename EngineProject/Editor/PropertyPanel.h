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

	FTransform* transform;

private:
	char                  InputBuf[256];
	TArray<FLogData>       Items;
	TArray<FString>		  Commands;
	TArray<FString>       History;
	int                   HistoryPos;
	ImGuiTextFilter       Filter;
	bool                  AutoScroll;
	bool                  ScrollToBottom;

};

