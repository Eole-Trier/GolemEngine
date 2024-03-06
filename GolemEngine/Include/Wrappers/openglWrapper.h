#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "dll.h"

class Vector4;

class GOLEM_ENGINE_API OpenglWrapper
{
private:
	// Static pointer which points to the only instance of this class
	static OpenglWrapper* m_instancePtr;

	unsigned int m_vao, m_vbo, m_rbo, m_fbo;
	unsigned int m_textureId;
	int m_width, m_height;

private:
	// Private constructor to stop intanciation
	OpenglWrapper() {}

public:
	// Returns instance of the class
	static OpenglWrapper* GetInstance();
	// Used to CREATE the scene in a framebuffer to be used as a texture. We do this in order to pass the texture to an ImGUI window so it can display it. 
	void CreateFramebuffer(int _width, int _height);
	void RescaleFramebuffer(float _width, float _height);
	// Used to BIND the scene in a framebuffer to be used as a texture. We do this in order to pass the texture to an ImGUI window so it can display it. 
	// The result is that we get a movable viewport in an ImGUI window.
	void BindFramebuffer();
	// Used to UNBIND the scene from a framebuffer to free the framebuffer. 
	void UnbindFramebuffer();
	// Used to clear a buffer for the next draw
	void ClearBuffer();
	// Used to set the background color of a buffer. Color is in the form of rgba vector. 
	void SetBackgroundColor(Vector4 _color);

	// This function is used to retrieve the texture of a framebuffer to use in the viewport to show the scene as a texture.
	unsigned int GetTextureId();
};