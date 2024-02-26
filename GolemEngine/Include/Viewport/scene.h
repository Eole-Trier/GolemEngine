#pragma once

#include "dll.h"
#include "Resource/resourceManager.h"
#include "Resource/shader.h"
#include "Viewport/camera.h"

class GOLEM_ENGINE_API Scene
{
private:
	ResourceManager m_resourceManager;
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

	// This function is used to create and bind the scene in a framebuffer to be used as a texture. We do this in order to pass the texture to an ImGUI window so it can display it. 
	// The result is that we get a movable viewport in an ImGUI window.
	void CreateFramebuffer();
	void RescaleFramebuffer(float _width, float _height);
	void Init();
	void BindFramebuffer();
	void UnbindFramebuffer();
	void Render(float _width, float _height, float _deltaTime);
};