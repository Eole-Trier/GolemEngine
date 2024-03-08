#pragma once
#include "UI/engineUi.h"
class BasicActors : public Window
{
public:
	BasicActors();
	~BasicActors();

	void Update(GolemEngine* _golemEngine, const char* _name = "default window") override;
};