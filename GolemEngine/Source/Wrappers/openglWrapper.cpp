#include "Wrappers/openglWrapper.h"

OpenglWrapper::OpenglWrapper() {}

OpenglWrapper::~OpenglWrapper() {} 

void OpenglWrapper::BindFramebuffer(GLuint& _framebuffer)
{
    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
}

void OpenglWrapper::UnbindFramebuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}