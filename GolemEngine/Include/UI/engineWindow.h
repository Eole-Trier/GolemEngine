#pragma once

#include "dll.h"
#include "basicActors.h"
#include "fileBrowser.h"
#include "engineWindow.h"
#include "viewport.h"
#include "Viewport/scene.h"

#include <string>

struct GLFWwindow;
struct GLFWmonitor;

class GOLEM_ENGINE_API EngineWindow
{
private:
	GLFWwindow* m_window = nullptr;
	GLFWmonitor* m_monitor = nullptr;
	std::string m_name;

	BasicActors* basicActors = nullptr;
	FileBrowser* fileBrowser = nullptr;
	Viewport* viewport = nullptr;
	
	float m_lastFrame = 0;

public:
	int screenWidth = 1800;
	int screenHeight = 1600;

	Scene* scene = nullptr;
	float deltaTime;

public:
	EngineWindow(const char* _name);
	~EngineWindow();

	GLFWwindow* GetWindow();

	void Init();
	void UpdateDeltaTime();
	void Render();
	void BeginDockSpace();
	void EndDockSpace();
	void Close();

	void ImGuiLoop();
	void ImGuiClean();

	void ProcessInput();
};