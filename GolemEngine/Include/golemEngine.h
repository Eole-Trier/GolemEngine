#pragma once

#include <string>

#include "dll.h"
#include "Viewport/scene.h"
//#include "Inputs/Mouse.h"

struct GLFWwindow;
class Scene;
class Camera;

class GOLEM_ENGINE_API GolemEngine
{
private:
	static GolemEngine* m_golemInstance;

	GLFWwindow* m_window = nullptr;
	Scene* m_scene = nullptr;
	Camera* m_camera = nullptr;
	int m_screenWidth = 0;
	int m_screenHeight = 0;
	float m_deltaTime = 0.f;

private:
	GolemEngine(GolemEngine& other) = delete;
	GolemEngine();

public:
	void operator=(const GolemEngine&) = delete;
	static GolemEngine* GetInstance();

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