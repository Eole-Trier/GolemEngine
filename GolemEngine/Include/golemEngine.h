#pragma once

#include <string>

#include "dll.h"
#include "Viewport/scene.h"

struct GLFWwindow;
class EngineUi;

class GOLEM_ENGINE_API GolemEngine
{
private:
	float m_deltaTime;
	std::string m_name;
	int m_screenWidth, m_screenHeight;

private:
	Scene* m_scene = nullptr;
	GLFWwindow* m_window = nullptr;
	EngineUi* m_engineUi = nullptr;

public:
	GolemEngine();
	~GolemEngine();

	void Init();
	void InitWindow();
	void InitScene();
	Scene* GetScene();
	GLFWwindow* GetGLFWWindow();
	void UpdateDeltaTime();
	float GetDeltaTime();
	float GetTime();
	void ProcessInput();
	void Update();
	void Close();
};