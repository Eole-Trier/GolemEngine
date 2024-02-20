#pragma once
#include "Resource/resourceManager.h"
#include "dll.h"
#include "Viewport/camera.h"

class GOLEM_ENGINE_API Scene
{
private:
	ResourceManager m_resourceManager;

public:
	Camera Camera;

public:
	Scene();

	void Init();
	void Update(float _width, float _height, GLFWwindow* _window, float _deltaTime);

};