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

public:
	Scene();

	// This function is used to create and bind the scene in a framebuffer to be used as a texture. We do this in order to pass the texture to an ImGUI window so it can display it. 
	// The result is that we get a movable viewport in an ImGUI window.
	void CreateFramebuffer();
	void RescaleFramebuffer(float _width, float _height);
	void Init();
	void Update(float _width, float _height, GLFWwindow* _window, float _deltaTime);

	void InitLights(Shader* shader);
	void UpdateLights(Shader* shader);

	void BindFramebuffer();
	void UnbindFramebuffer();
};