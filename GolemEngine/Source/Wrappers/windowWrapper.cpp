#include "Wrappers/windowWrapper.h"

#include "Image/stb_image.h"


void WindowWrapper::InitWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
}

GLFWwindow* WindowWrapper::NewWindow(int _width, int _height, const char* _title, GLFWmonitor* _monitor, GLFWwindow* _share)
{
    return glfwCreateWindow(_width, _height, _title, _monitor, _share);
}

void WindowWrapper::Terminate()
{
    glfwTerminate();
}

int WindowWrapper::ShouldWindowClose(GLFWwindow* _window)
{
    return glfwWindowShouldClose(_window);
}

void WindowWrapper::ProcessEvents()
{
    glfwPollEvents();
}

void WindowWrapper::SwapBuffers(GLFWwindow* _window)
{
    glfwSwapBuffers(_window);
}

GLFWwindow* WindowWrapper::GetCurrentWindow()
{
    return glfwGetCurrentContext();
}

void WindowWrapper::SetCurrentWindow(GLFWwindow* _window)
{
    glfwMakeContextCurrent(_window);
}

GLuint WindowWrapper::LoadUiTexture(const char* _filename)
{
    int width, height, channels;
    unsigned char* data = stbi_load(_filename, &width, &height, &channels, 0);
    if (!data) {
        return 0;
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(data);

    return texture;
}

//void WindowWrapper::SetScrollCallback(ScrollCallback callback)
//{
//}
