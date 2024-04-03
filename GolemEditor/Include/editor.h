#pragma once

#include "Core/scene.h"

class EditorUi;
struct GLFWwindow;

class Editor
{
private:
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