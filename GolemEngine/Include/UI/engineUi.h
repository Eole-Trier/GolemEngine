#pragma once

#include "dll.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class BasicActors;
class Viewport;
class FileBrowser;
class WorldActors;
class DebugWindow;
class GolemEngine;

class GOLEM_ENGINE_API Window
{
public:
	GLFWwindow* window;
};

class GOLEM_ENGINE_API EngineUi
{
private:
	Viewport* m_viewport = nullptr;
	WorldActors* m_worldActors= nullptr;
	GolemEngine* m_golemEngine= nullptr;
	FileBrowser* m_fileBrowser = nullptr;
	DebugWindow* m_debugWindow = nullptr;
	BasicActors* m_basicActors = nullptr;

public:
	EngineUi(GolemEngine* _golemEngine);
	~EngineUi();

	void BeginDockSpace();
	void EndDockSpace();
	void UpdateLoop();
};