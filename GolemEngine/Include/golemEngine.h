#pragma once

#include <string>

#include "dll.h"

struct GLFWwindow;
class Scene;

class GOLEM_ENGINE_API GolemEngine
{
private:
	float m_deltaTime = 0.f;

	GLFWwindow* m_window = nullptr;
	Scene* m_scene = nullptr;

	int m_screenWidth = 0;
	int m_screenHeight = 0;

public:
	GolemEngine();

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

	void SetScreenSize(int _width, int _height);
	void SetWindow(GLFWwindow* _window);
};