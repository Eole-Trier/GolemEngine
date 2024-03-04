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
	Viewport* m_viewport = nullptr;
	FileBrowser* m_fileBrowser = nullptr;
	WorldActors* m_worldActors= nullptr;
	DebugWindow* m_debugWindow = nullptr;
	GolemEngine* m_golemEngine= nullptr;

public:
	EngineUi(GolemEngine* _golemEngine);
	~EngineUi();

	void BeginDockSpace();
	void EndDockSpace();
	void UpdateLoop();

	void SetViewport(int _width, int _height);
	Viewport* GetViewport();
};