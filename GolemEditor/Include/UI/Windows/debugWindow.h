#pragma once

#include "UI/Windows/window.h"

class GolemEngine;

class DebugWindow : public Window
{
public:
	DebugWindow(std::string _name);
	~DebugWindow();

	void Update(GolemEngine* _golemEngine);
};