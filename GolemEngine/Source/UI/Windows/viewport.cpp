#include "UI/Windows/viewport.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Viewport/camera.h"
#include "golemEngine.h"

Camera* Viewport::m_camera = new Camera(Vector3(0.0f, 0.0f, 3.0f));

Viewport::Viewport()
{
    m_lastX = 0;
    m_lastY = 0;
    m_yaw = 0;
    m_pitch = 0;
    m_firstMouse = true;
}

Viewport::~Viewport() {}

void Viewport::Update(GolemEngine* _golemEngine)
{
    glEnable(GL_DEPTH_TEST);

    ImGui::Begin("Viewport");

    ImGui::Image((ImTextureID)_golemEngine->GetScene()->textureId, ImGui::GetContentRegionAvail());

    if (ImGui::IsWindowFocused())
    {
        m_camera->ProcessInput(_golemEngine->GetGLFWWindow(), _golemEngine->GetDeltaTime());
        MouseMovement(_golemEngine);
        glfwSetScrollCallback(_golemEngine->GetGLFWWindow(), ScrollCallback);
    }

    ImGui::End();
}

void Viewport::MouseCallback(GolemEngine* _golemEngine, double _xposIn, double _yposIn)
{
    float xpos = (float)(_xposIn);
    float ypos = (float)(_yposIn);

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

    m_camera->ProcessMouseMovement(xoffset, yoffset);
}

void Viewport::ScrollCallback(GLFWwindow* _window, double _xoffset, double _yoffset)
{
    m_camera->ProcessMouseScroll(_yoffset);
}

Camera* Viewport::GetCamera()
{
    return m_camera;
}

void Viewport::MouseMovement(GolemEngine* _golemEngine)
{
    glfwGetCursorPos(_golemEngine->GetGLFWWindow(), &m_cursorX, &m_cursorY);
    if (glfwGetKey(_golemEngine->GetGLFWWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        glfwSetInputMode(_golemEngine->GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        MouseCallback(_golemEngine, m_cursorX, -m_cursorY);
    }
    else
    {
        m_firstMouse = true;
        glfwSetInputMode(_golemEngine->GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}