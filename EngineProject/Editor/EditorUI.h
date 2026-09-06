#pragma once

#include "EditorPanel.h"

class FEditorUI
{
public:
	bool Init();
	void OnRender();

	template <typename T>
	T* AddEditorPanel()
	{
		TUniquePtr<T> newPanel = MakeUnqiue<T>();
		Panels.push_back(newPanel);
		return newPanel.get();
	}
private:
	TArray<TUniquePtr<IEditorPanel>> Panels;
};