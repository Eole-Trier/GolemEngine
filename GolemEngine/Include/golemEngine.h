#pragma once

#include <string>

#include "dll.h"
#include "Viewport/scene.h"
#include "UI/Windows/viewport.h"
#include "Inputs/Mouse.h"

struct GLFWwindow;
class Scene;

class GOLEM_ENGINE_API GolemEngine
{
private:
	GLFWwindow* m_window = nullptr;
	Scene* m_scene = nullptr;
	int m_screenWidth = 0;
	int m_screenHeight = 0;
	float m_deltaTime = 0.f;

public:
	GolemEngine();
	~GolemEngine();

	void InitScene();
	void Init();
	void UpdateDeltaTime();
	void ProcessInput();
	void Update();
	void Close();

	Scene* GetScene();
	GLFWwindow* GetWindow();
	float GetDeltaTime();
	float GetTime();

	void SetScreenSize(int _width, int _height);
	void SetWindow(GLFWwindow* _window);
};