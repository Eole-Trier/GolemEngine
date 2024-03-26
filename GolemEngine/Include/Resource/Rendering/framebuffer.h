#pragma once

#pragma once
#include "Wrappers/graphicWrapper.h"

class Framebuffer
{
private:
	unsigned int m_fbo;

public:
	Framebuffer();
	~Framebuffer();

	void Bind();

	void TextureAttachement(int _width, int _height);

};