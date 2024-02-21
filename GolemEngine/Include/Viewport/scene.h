#pragma once
#include "Resource/resourceManager.h"
#include "dll.h"
#include "Viewport/camera.h"

class DirectionalLight;
class PointLight;
class SpotLight;
class Shader;

class GOLEM_ENGINE_API Scene
{
private:
	ResourceManager m_resourceManager;
	std::vector<DirectionalLight*> dirLights;
	std::vector<PointLight*> pointLights;
	std::vector<SpotLight*> spotLights;

public:
	Camera Camera;

public:
	Scene();

	void Init();
	void Update(float _width, float _height, GLFWwindow* _window, float _deltaTime);

	void InitLights(Shader* shader);
	void UpdateLights(Shader* shader);

};