#pragma once

#include "dll.h"
#include "basicActors.h"
#include "fileBrowser.h"

#include <string>

struct GLFWwindow;
struct GLFWmonitor;

//class FileBrowser;
//class Viewport;
//class WorldActors;

class GOLEM_ENGINE_API EngineWindow
{
private:
	GLFWwindow* m_window = nullptr;
	GLFWmonitor* m_monitor = nullptr;
	std::string m_name;

	BasicActors* basicActors = new BasicActors();
	FileBrowser* fileBrowser = new FileBrowser();

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
	void Close();

	void ImGuiLoop();
	void ImGuiClean();

	void ProcessInput();
};