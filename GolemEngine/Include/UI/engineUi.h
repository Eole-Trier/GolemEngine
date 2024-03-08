#pragma once

#include "dll.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

class BasicActors;
class Viewport;
class FileBrowser;
class WorldActors;
class DebugWindow;
class GolemEngine;

class GOLEM_ENGINE_API Window
{
private:
	const char* m_name;

public:
	bool isRendered = true;
	GLFWwindow* window;
	
	virtual void Update(GolemEngine* _golemEngine, const char* _name = "default window");
};

class GOLEM_ENGINE_API EngineUi
{
private:
	std::vector<Window*> m_windowList;

	BasicActors* m_basicActors = nullptr;
	FileBrowser* m_fileBrowser = nullptr;
	WorldActors* m_worldActors = nullptr;
	DebugWindow* m_debugWindow = nullptr;
	GolemEngine* m_golemEngine = nullptr;

	bool m_isFullscreen = false;

public:
	Viewport* m_viewport = nullptr;
	EngineUi(GolemEngine* _golemEngine);
	~EngineUi();

	void InitUI(GLFWwindow* _window);
	void Update();
	void CustomWindows();

	bool GetIsFullscreen();
	void SetIsFullscreen(bool _value);
	Viewport* GetViewport();

	void AddNewWindow(Window* _newWindow);
};