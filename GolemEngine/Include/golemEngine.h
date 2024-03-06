#pragma once

#include <string>

#include "dll.h"
#include "Viewport/scene.h"

struct GLFWwindow;
class EngineUi;
class OpenglWrapper;

class GOLEM_ENGINE_API GolemEngine
{
private:
	GLFWwindow* m_window = nullptr;
	std::string m_name;
	int m_screenWidth, m_screenHeight;

	Scene* m_scene = nullptr;
	EngineUi* m_engineUi = nullptr;

	float m_deltaTime;

	

public:
	GolemEngine();
	~GolemEngine();

	void InitWindow();
	void InitScene();
	void Init();
	void UpdateDeltaTime();
	void ProcessInput();
	void Update();
	void Close();

	Scene* GetScene();
	GLFWwindow* GetGlfwWindow();
	float GetDeltaTime();
	float GetTime();
};