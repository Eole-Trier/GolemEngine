#pragma once

#include "UI/engineWindow.h"
#include "Viewport/scene.h"

class Editor
{
private:
	EngineWindow* m_engineWindow = nullptr;
	Scene* m_scene = nullptr;

public:
	Editor();
	~Editor();

	void Init();
	void Run();
	void MainLoop();
	void Cleanup();
};