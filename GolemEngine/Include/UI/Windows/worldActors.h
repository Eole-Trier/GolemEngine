#pragma once
#include "UI/engineUi.h"

class WorldActors : public Window
{
public:
	WorldActors();
	~WorldActors();

	void Update(GolemEngine* _golemEngine, const char* _name = "default window") override;
};