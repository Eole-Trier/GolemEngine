#pragma once

#include <string>
#include <vector>

#include "dll.h"
#include "Viewport/scene.h"


struct GLFWwindow;
class Camera;

class GOLEM_ENGINE_API GolemEngine
{
private:
	static inline std::vector<Scene*> m_scenes;
	static inline Scene* m_currentScene = nullptr;
	static inline Camera* m_camera = nullptr;
	static inline float m_deltaTime = 0.f;

private:
	// Private constructors and destructor to make static class
	GolemEngine() = delete;
	GolemEngine(GolemEngine& _other) = delete;
	GolemEngine(GolemEngine&& _other) = delete;
	GolemEngine& operator=(GolemEngine& _other) = delete;
	GolemEngine& operator=(GolemEngine&& _other) = delete;
	void operator=(const GolemEngine&) = delete;
	~GolemEngine() = delete;

public:
	static void InitScene();
	static void Init();
	static void UpdateDeltaTime();
	static void ProcessInput();
	static void Update();
	static void Close();

	static Scene* GetCurrentScene();
	static Camera* GetCamera();
	static float GetDeltaTime();
	static float GetTime();

	static void SetCurrentScene(int _sceneId);
};