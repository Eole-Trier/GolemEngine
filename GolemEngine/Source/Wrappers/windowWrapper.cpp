#include "Wrappers/windowWrapper.h"

#include <GLFW/glfw3.h>


WindowWrapper* WindowWrapper::m_instancePtr = nullptr;

WindowWrapper::WindowWrapper() {}

WindowWrapper* WindowWrapper::GetInstance()
{
    if (!m_instancePtr) {
        m_instancePtr = new WindowWrapper();
    }
    return m_instancePtr;
}

int WindowWrapper::Init()
{
    return glfwInit();
}

void WindowWrapper::SetOption(int _hint, int _value)
{
    glfwWindowHint(_hint, _value);
}

GLFWwindow* WindowWrapper::NewWindow(int _width, int _height, const char* _title, GLFWmonitor* _monitor, GLFWwindow* _share)
{
    return glfwCreateWindow(_width, _height, _title, _monitor, _share);
}

void WindowWrapper::Terminate()
{
    glfwTerminate();
}

void WindowWrapper::SetCurrentWindow(GLFWwindow* _window)
{
    glfwMakeContextCurrent(_window);
}

void WindowWrapper::ProcessEvents()
{
    glfwPollEvents();
}

void WindowWrapper::SwapBuffers(GLFWwindow* _window)
{
    glfwSwapBuffers(_window);
}

int WindowWrapper::ShouldWindowClose(GLFWwindow* _window)
{
    return glfwWindowShouldClose(_window);
}