#pragma once

#include "dll.h"
#include "basicActors.h"
#include "fileBrowser.h"
#include "engineWindow.h"
#include "viewport.h"
#include "debugWindow.h"
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
	int m_lastFrame = 0;
	BasicActors* m_basicActors = nullptr;
	FileBrowser* m_fileBrowser = nullptr;
	Viewport* m_viewport = nullptr;
	DebugWindow* m_debugWindow = nullptr;

public:
	int screenWidth = 1800;
	int screenHeight = 1600;

	Scene* scene = nullptr;
	float time = 0.0f, deltaTime = 0.0f;

public:
	EngineWindow(const char* _name);
	~EngineWindow();

	// Init engine main window.
	void Init();
	void UpdateDeltaTime();
	// Update all ImGUI windows
	void ImGuiLoop();
	// Setup the dock space for our different ImGui windows
	void BeginDockSpace();
	void EndDockSpace();
	// Process user inputs
	void ProcessInput();
	// Render all ImGUI windows
	void Render();
	void Close();
	void ImGuiClean();
};