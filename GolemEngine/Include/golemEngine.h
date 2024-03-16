#pragma once

#include <string>

#include "dll.h"

struct GLFWwindow;
class Scene;
class Camera;

class GOLEM_ENGINE_API GolemEngine
{
private:
	GLFWwindow* m_window = nullptr;
	Scene* m_scene = nullptr;
	Camera* m_camera = nullptr;
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

	GLFWwindow* GetWindow();
	Scene* GetScene();
	Camera* GetCamera();
	float GetDeltaTime();
	float GetTime();

	void SetScreenSize(const int _width, const int _height);
	void SetWindow(GLFWwindow* _window);
};