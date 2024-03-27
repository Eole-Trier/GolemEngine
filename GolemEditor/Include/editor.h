#pragma once

#include "Viewport/scene.h"

class GolemEngine;
class EditorUi;
struct GLFWwindow;

class Editor
{
private:
	GolemEngine* m_golemEngine = nullptr;
	std::string m_name;

public:
	Editor();
	~Editor();

	void InitWindow();
	void InitGraphics();
	void InitUi();
	void Init();
	void Run();
	void MainLoop();
	void Cleanup();
};