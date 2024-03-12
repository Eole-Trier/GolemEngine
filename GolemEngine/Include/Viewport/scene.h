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
	std::vector<DirectionalLight*> m_dirLights;
	std::vector<PointLight*> m_pointLights;
	std::vector<SpotLight*> m_spotLights;
	unsigned int m_sceneTexture;

public:
	unsigned int vao = 0;
	unsigned int vbo = 0;
	unsigned int rbo = 0;
	unsigned int fbo = 0;
	unsigned int textureId = 0;

public:
	Scene();

	void Init();
	void Update(float _width, float _height, GLFWwindow* _window, Camera* _camera, float _deltaTime);
	void InitLights();
	void UpdateLights(Shader* _shader);
};