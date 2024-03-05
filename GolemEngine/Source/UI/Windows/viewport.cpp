#include "UI/Windows/viewport.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Viewport/camera.h"
#include "golemEngine.h"

float Viewport::m_lastX = 400;
float Viewport::m_lastY = 300;
float Viewport::m_yaw = 0;
float Viewport::m_pitch = 0;
bool Viewport::m_firstMouse = true;


Viewport::Viewport(GolemEngine* _golemEngine)
{
   
}

Viewport::~Viewport() {}

void Viewport::Update(GolemEngine* _golemEngine)
{
    glEnable(GL_DEPTH_TEST);

    ImGui::Begin("Viewport");
    ImGui::Image((ImTextureID)_golemEngine->GetScene()->textureId, ImGui::GetContentRegionAvail());
    _golemEngine->GetScene()->camera.ProcessInput(_golemEngine->GetGLFWWindow(), _golemEngine->GetDeltaTime());
    MouseCallback(_golemEngine->GetGLFWWindow(), ImGui::GetCursorPosX(), ImGui::GetCursorPosX());
    ImGui::End();
}

void Viewport::ResizeCallback(GLFWwindow* window, int _width, int _height)
{
    glViewport(0, 0, _width, _height);
}


void Viewport::MouseCallback(GLFWwindow* _window, double _xposIn, double _yposIn)
{
    float xpos = static_cast<float>(_xposIn);
    float ypos = static_cast<float>(_yposIn);

    if (m_firstMouse)
    {
        m_lastX = xpos;
        m_lastY = ypos;
        m_firstMouse = false;
    }

    float xoffset = xpos - m_lastX;
    float yoffset = m_lastY - ypos;

    m_lastX = xpos;
    m_lastY = ypos;

    Camera* const cam = Camera::instance;
    if (glfwGetKey(_window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        cam->ProcessMouseMovement(xoffset, yoffset);
    }
}

void Viewport::ScrollCallback(GLFWwindow* _window, double _xoffset, double _yoffset)
{
    Camera* const cam = Camera::instance;
    cam->ProcessMouseScroll(_yoffset);
}
