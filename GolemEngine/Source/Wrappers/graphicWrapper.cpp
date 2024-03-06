#include "Wrappers/graphicWrapper.h"

#include <iostream>

#include "vector4.h"

GraphicWrapper* GraphicWrapper::m_instancePtr = nullptr;

GraphicWrapper* GraphicWrapper::GetInstance()
{
    if (!m_instancePtr) {
        m_instancePtr = new GraphicWrapper();
    }
    return m_instancePtr;
}

void GraphicWrapper::EnableDepth()
{
    glEnable(GL_DEPTH_TEST);
}

void GraphicWrapper::CreateFramebuffer(int _width, int _height)
{
    // Create framebuffer
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    // Create texturebuffer
    glGenTextures(1, &m_textureId);
    glBindTexture(GL_TEXTURE_2D, m_textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureId, 0);

    // Create renderbuffer
    glGenRenderbuffers(1, &m_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

    // Check framebuffer completeness
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "Framebuffer is not complete." << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);   // Unbind framebuffer
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);   // Unbind framebuffer
    glBindTexture(GL_TEXTURE_2D, 0);    // Unbind texture
    glBindRenderbuffer(GL_RENDERBUFFER, 0); // Unbind renderbuffer
}

void GraphicWrapper::RescaleFramebuffer(float _width, float _height)
{
    glBindTexture(GL_TEXTURE_2D, m_textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureId, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);
}

void GraphicWrapper::BindFramebuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

void GraphicWrapper::UnbindFramebuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GraphicWrapper::ClearBuffer()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GraphicWrapper::SetBackgroundColor(Vector4 _color)
{
    glClearColor(_color.x, _color.y, _color.z, _color.w);
}

void GraphicWrapper::SetViewport(GLint _xMin, GLint _yMin, GLsizei _xMax, GLsizei _yMax)
{
    glViewport(_xMin, _yMin, _xMax, _yMax);
}

unsigned int GraphicWrapper::GetTextureId()
{
    return m_textureId;
}