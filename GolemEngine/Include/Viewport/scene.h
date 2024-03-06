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
	std::vector<DirectionalLight*> dirLights;
	std::vector<PointLight*> pointLights;
	std::vector<SpotLight*> spotLights;
	unsigned int m_sceneTexture;

public:
	unsigned int vao, vbo, rbo;
	unsigned int fbo;
	unsigned int textureId;
	Camera camera;
	Shader* shad;
	int width, height;

public:
	Scene();

	void Init();
	void Update(float _width, float _height, GLFWwindow* _window, float _deltaTime);
	void InitLights(Shader* _shader);
	void UpdateLights(Shader* _shader);
};