#pragma once

class GolemEngine;

class DebugWindow
{
public:
	DebugWindow();
	~DebugWindow();

	void Update(GolemEngine* _golemEngine, const char* _name = "default window");
};