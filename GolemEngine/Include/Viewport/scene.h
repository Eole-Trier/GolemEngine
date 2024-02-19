#pragma once
#include "Resource/resourceManager.h"
#include "dll.h"
#include "Viewport/camera.h"

class GOLEM_ENGINE_API Scene
{
private:
	ResourceManager m_resourceManager;
	Camera m_camera;

public:
	Scene();

	void Init();
	void Update(float _width, float _height);
};