#pragma once

#include "UI/editorWindow.h"

class WorldActors : public EditorWindow
{
public:
	WorldActors();
	~WorldActors();

	void Update(GolemEngine* _golemEngine, const char* _name = "default window") override;
};