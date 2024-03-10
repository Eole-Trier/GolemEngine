#pragma once

#include <vector>

class GolemEngine;
class Viewport;
class BasicActors;
class FileBrowser;
class WorldActors;
class DebugWindow;
struct GLFWwindow;

class EditorUi
{
private:
	GolemEngine* m_golemEngine = nullptr;
	Viewport* m_viewport = nullptr;
	BasicActors* m_basicActors = nullptr;
	FileBrowser* m_fileBrowser = nullptr;
	WorldActors* m_worldActors = nullptr;
	DebugWindow* m_debugWindow = nullptr;

	bool m_isFullscreen = false;

public:
	EditorUi(GolemEngine* _golemEngine);

	void Init(GLFWwindow* _window);
	void BeginDockSpace();
	void EndDockSpace();
	void UpdateWindows();

	bool GetIsFullscreen();
	void SetIsFullscreen(bool _value);
	Viewport* GetViewport();
};