#pragma once

#include "dll.h"

class BasicActors;
class Viewport;
class FileBrowser;
class WorldActors;
class DebugWindow;
class GolemEngine;

class GOLEM_ENGINE_API EngineUi
{
private:
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

	void BeginDockSpace();
	void EndDockSpace();
	void UpdateLoop();

	bool GetIsFullscreen();
	void SetIsFullscreen(bool _value);
	void SetViewport(int _width, int _height);
	Viewport* GetViewport();
};