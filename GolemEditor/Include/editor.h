#pragma once

#include "Viewport/window.h"

class Editor
{
private:
	Window* m_viewport = new Window("Viewport", 800, 600);

public:
	Editor();
	~Editor();

	void Init();
	void Run();
	void MainLoop();
	void Cleanup();
};