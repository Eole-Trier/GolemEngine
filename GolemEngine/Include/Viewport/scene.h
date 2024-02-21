#pragma once

#include "Resource/resourceManager.h"
#include "dll.h"
#include "Viewport/camera.h"

class GOLEM_ENGINE_API Scene
{
private:
	ResourceManager m_resourceManager;
	unsigned int m_sceneTexture;

public:
	unsigned int m_fbo;
	Camera Camera;
	int width, height;

public:
	Scene();

	// This function is used to create and bind the scene in a framebuffer to be used as a texture. We do this in order to pass the texture to an ImGUI window so it can display it. 
	// The result is that we get a movable viewport in an ImGUI window.
	void Init();
	void InitObjects();
	void Update(float _width, float _height, GLFWwindow* _window, float _deltaTime);

};