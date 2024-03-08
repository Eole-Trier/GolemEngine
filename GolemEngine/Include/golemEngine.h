#pragma once

#include <string>

#include "dll.h"

struct GLFWwindow;
class Scene;

class GOLEM_ENGINE_API GolemEngine
{
private:
	float m_deltaTime;

	GLFWwindow* m_window = nullptr;
	Scene* m_scene = nullptr;

	int m_screenWidth;
	int m_screenHeight;

public:
	GolemEngine(int _screenWidth, int _screenHeight);

	void Init();
	void InitScene();
	void UpdateDeltaTime();
	void Update();
	void ProcessInput();
	void Close();

	Scene* GetScene();
	GLFWwindow* GetWindow();

	float GetDeltaTime();
	float GetTime();

	float GetScreenWidth();
	float GetScreenHeight();
};