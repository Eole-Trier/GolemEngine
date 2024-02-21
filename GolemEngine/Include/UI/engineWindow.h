#pragma once

#include "dll.h"
#include "basicActors.h"
#include "fileBrowser.h"
#include "engineWindow.h"
#include "viewport.h"

#include <string>

struct GLFWwindow;
struct GLFWmonitor;

class GOLEM_ENGINE_API EngineWindow
{
private:
	GLFWwindow* m_window = nullptr;
	GLFWmonitor* m_monitor = nullptr;
	std::string m_name;

public:
	int screenWidth = 1800;
	int screenHeight = 1600;

public:
	EngineWindow();
	~EngineWindow();
	EngineWindow(const char* _name);
	EngineWindow(const char* _name, unsigned int _width, unsigned int _height);

	GLFWwindow* GetWindow();

	void Init();
	void Render();
	void BeginDockSpace();
	void EndDockSpace();
	void Close();

	void ImGuiLoop();
	void ImGuiClean();

	void ProcessInput();
};