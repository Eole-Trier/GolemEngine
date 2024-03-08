#pragma once

#include "UI/editorWindow.h"

class BasicActors : public EditorWindow
{
public:
	BasicActors();
	~BasicActors();

	void Update(GolemEngine* _golemEngine, const char* _name = "default window") override;
};