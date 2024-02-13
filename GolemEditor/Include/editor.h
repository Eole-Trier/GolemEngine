#pragma once

#include "Viewport/window.h"

class Editor
{
private:
	Window* m_viewport = nullptr;

public:
	Editor();
	~Editor();

	void Init();
	void Run();
	void MainLoop();
	void Cleanup();
};