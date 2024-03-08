#pragma once

#include <vector>

#include "UI/editorWindow.h"

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

	std::vector<EditorWindow*> m_windowList;

	bool m_isFullscreen = false;

public:
	EditorUi(GolemEngine* _golemEngine);

	void Init(GLFWwindow* _window);
	void Update();
	void CustomWindow();		// TEMP

	bool GetIsFullscreen();
	void SetIsFullscreen(bool _value);
	Viewport* GetViewport();
};