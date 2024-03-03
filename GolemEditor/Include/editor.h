#pragma once

#include "Viewport/scene.h"

class GolemEngine;

class Editor
{
private:
	GolemEngine* m_golemEngine = nullptr;

public:
	Editor();
	~Editor();

	void Init();
	void Run();
	void MainLoop();
	void Cleanup();
};