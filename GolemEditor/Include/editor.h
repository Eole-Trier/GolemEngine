#pragma once

#include "Viewport/scene.h"

class GolemEngine;
class EditorUi;
struct GLFWwindow;

class Editor
{
private:
	GolemEngine* m_golemEngine = nullptr;
	EditorUi* m_editorUi = nullptr;

	GLFWwindow* m_window = nullptr;
	std::string m_name;
	int m_screenWidth, m_screenHeight;

public:
	Editor();
	~Editor();

	void InitWindow();
	void Init();
	void Run();
	void MainLoop();
	void Cleanup();
};