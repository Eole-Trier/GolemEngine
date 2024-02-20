#pragma once

class EngineWindow;
class Scene;

class Editor
{
private:
	EngineWindow* m_engineWindow = nullptr;
	Scene* m_scene = nullptr;

public:
	Editor();
	~Editor();

	void Init();
	void Run();
	void MainLoop();
	void Cleanup();
};