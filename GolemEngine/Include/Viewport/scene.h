#pragma once

#include "dll.h"
#include "Resource/resourceManager.h"
#include "Viewport/camera.h"

class DirectionalLight;
class PointLight;
class SpotLight;
class Shader;

class GOLEM_ENGINE_API Scene
{
private:
	ResourceManager m_resourceManager;

	static constexpr size_t m_maxDirLights = 1;
	static constexpr size_t m_maxPointLights = 10; // According to the shader
	static constexpr size_t m_maxSpotLights = 10;

	std::vector<DirectionalLight*> m_dirLights;
	std::vector<PointLight*> m_pointLights;
	std::vector<SpotLight*> m_spotLights;

public:
	Scene();

	void Init();
	void Update(float _width, float _height, GLFWwindow* _window, Camera* _camera, float _deltaTime);
	void InitLights();
	void UpdateLights(Shader* _shader);
};