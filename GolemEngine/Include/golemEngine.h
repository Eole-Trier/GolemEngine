#pragma once

#include <string>

#include "dll.h"
#include "Viewport/scene.h"
#include "UI/Windows/viewport.h"

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

	void Init();
	void InitWindow();
	void InitScene();
	void UpdateDeltaTime();
	void Update();
	void ProcessInput();
	void Close();

	Scene* GetScene();
	GLFWwindow* GetWindow();
	float GetDeltaTime();
	float GetTime();
};