#pragma once

class IEditorPanel
{
public:
	virtual ~IEditorPanel() = default;

	virtual bool Init() = 0;
	virtual void OnRender() = 0;
};