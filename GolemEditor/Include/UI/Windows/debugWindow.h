#pragma once

#include "UI/editorWindow.h"

class DebugWindow : public EditorWindow
{
public:
	DebugWindow();
	~DebugWindow();

	void Update(GolemEngine* _golemEngine, const char* _name = "default window") override;
};