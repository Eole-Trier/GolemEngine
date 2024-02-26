#pragma once

#include <string>

#include "dll.h"
#include "Viewport/scene.h"

struct GLFWwindow;
class EngineUi;

class GOLEM_ENGINE_API GolemEngine
{
private:
	GLFWwindow* m_window = nullptr;
	std::string m_name;
	int m_screenWidth, m_screenHeight;

	Scene* m_scene = nullptr;
	EngineUi* m_engineUi = nullptr;

	int m_lastFrame = 0;
	float m_deltaTime;
	float m_time;

public:
	GolemEngine();
	~GolemEngine();

	void InitWindow();
	void InitScene();
	void Init();
	Scene* GetScene();
	void UpdateDeltaTime();
	float GetDeltaTime();
	float GetTime();
	void ProcessInput();
	void Render();
	void Close();
};