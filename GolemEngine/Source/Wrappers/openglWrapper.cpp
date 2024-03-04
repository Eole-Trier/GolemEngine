#include "Wrappers/openglWrapper.h"

#include <iostream>

OpenglWrapper::OpenglWrapper() {}

OpenglWrapper::~OpenglWrapper() {} 

GLuint OpenglWrapper::CreateFramebuffer(int _width, int _height)
{
    // Create framebuffer
    GLuint framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    // Create texturebuffer
    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId, 0);

    // Create renderbuffer
    GLuint renderbuffer;
    glGenRenderbuffers(1, &renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer);

    // Check framebuffer completeness
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) 
    {
        std::cout << "Framebuffer is not complete." << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);   // Unbind framebuffer
        return 0;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);   // Unbind framebuffer
    glBindTexture(GL_TEXTURE_2D, 0);    // Unbind texture
    glBindRenderbuffer(GL_RENDERBUFFER, 0); // Unbind renderbuffer

    return framebuffer;
}



void OpenglWrapper::BindFramebuffer(GLuint& _framebuffer)
{
    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
}

void OpenglWrapper::UnbindFramebuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}