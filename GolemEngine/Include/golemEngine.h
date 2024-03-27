#pragma once

#include <string>

#include "dll.h"
#include "Viewport/scene.h"

struct GLFWwindow;
class Scene;
class Camera;

class GOLEM_ENGINE_API GolemEngine
{
private:
	static GolemEngine* m_golemInstance;

	Scene* m_scene = nullptr;
	Camera* m_camera = nullptr;
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

	Scene* GetScene();
	Camera* GetCamera();
	float GetDeltaTime();
	float GetTime();
};