#include "Wrappers/windowWrapper.h"

#include <GLFW/glfw3.h>


WindowWrapper* WindowWrapper::m_instancePtr = nullptr;

WindowWrapper::WindowWrapper() {}

WindowWrapper* WindowWrapper::GetInstance()
{
    if (!m_instancePtr) 
    {
        m_instancePtr = new WindowWrapper();
    }
    return m_instancePtr;
}

void WindowWrapper::Init()
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

//void WindowWrapper::SetScrollCallback(ScrollCallback callback)
//{
//}
