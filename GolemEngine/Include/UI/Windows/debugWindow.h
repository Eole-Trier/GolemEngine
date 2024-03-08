#pragma once
#include "UI/engineUi.h"

class DebugWindow : public Window
{
public:
	DebugWindow();
	~DebugWindow();

	void Update(GolemEngine* _golemEngine, const char* _name = "default window") override;
};