#pragma once

#include "UI/engineWindow.h"

class Editor
{
private:
	EngineWindow* m_viewport = nullptr;

public:
	Editor();
	~Editor();

	void Init();
	void Run();
	void MainLoop();
	void Cleanup();
};