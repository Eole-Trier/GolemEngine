#pragma once

#include "Viewport/scene.h"

class GolemEngine;
class EditorUi;
class Editor
{
private:
	GolemEngine* m_golemEngine = nullptr;
	EditorUi* m_editorUi = nullptr;

public:
	Editor();
	~Editor();

	void Init();
	void Run();
	void MainLoop();
	void Cleanup();
};