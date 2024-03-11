#pragma once

#include <vector>

class GolemEngine;
class BasicActors;
class Viewport;
class FileBrowser;
class WorldActors;
class DebugWindow;
struct GLFWwindow;

class EditorUi
{
private:
	GolemEngine* m_golemEngine = nullptr;
	BasicActors* m_basicActors = nullptr;
	Viewport* m_viewport = nullptr;
	FileBrowser* m_fileBrowser = nullptr;
	WorldActors* m_worldActors = nullptr;
	DebugWindow* m_debugWindow = nullptr;

public:
	EditorUi(GolemEngine* _golemEngine);

	void Init(GLFWwindow* _window);
	void BeginDockSpace();
	void EndDockSpace();
	void UpdateWindows();
};