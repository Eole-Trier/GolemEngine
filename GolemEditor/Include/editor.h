#pragma once

#include "UI/engineWindow.h"

class Editor
{
private:
	EngineWindow* m_engineWindow = nullptr;

public:
	Editor();
	~Editor();

	void Init();
	void Run();
	void MainLoop();
	void Cleanup();
};