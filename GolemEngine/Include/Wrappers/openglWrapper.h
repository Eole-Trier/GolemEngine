#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "dll.h"

class GOLEM_ENGINE_API OpenglWrapper
{
public:
	OpenglWrapper();
	~OpenglWrapper();
	
	GLuint CreateFramebuffer(int _width, int _height);
	void BindFramebuffer(GLuint& _framebuffer);
	void UnbindFramebuffer();
};