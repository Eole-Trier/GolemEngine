#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "dll.h"

class GOLEM_ENGINE_API OpenglWrapper
{
public:
	OpenglWrapper();
	~OpenglWrapper();
	
	void BindFramebuffer(GLuint& _framebuffer);
	void UnbindFramebuffer();
};