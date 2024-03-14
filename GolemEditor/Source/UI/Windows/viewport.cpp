#include "UI/Windows/viewport.h"

#include <GLFW/glfw3.h>

#include "Viewport/camera.h"
#include "golemEngine.h"
#include "Wrappers/graphicWrapper.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

Camera* Viewport::m_camera = new Camera(Vector3(0.0f, 0.0f, 3.0f));


Viewport::Viewport()
    :m_lastX(0),
    m_lastY(0),
    m_yaw(0),
    m_pitch(0),
    m_firstMouse(true)
{}

Viewport::~Viewport() {}

void Viewport::Update(GolemEngine* _golemEngine, const char* _name)
{
    GraphicWrapper::EnableDepth();

    ImGui::Begin("Viewport");

    ImGui::Image((ImTextureID)GraphicWrapper::GetTextureId(), ImGui::GetContentRegionAvail());

    if (ImGui::IsWindowFocused())
    {
        Camera::instance->ProcessInput(_golemEngine->GetWindow(), _golemEngine->GetDeltaTime());
        MouseMovement(_golemEngine);
        glfwSetScrollCallback(_golemEngine->GetWindow(), ScrollCallback);
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

    Camera::instance->ProcessMouseMovement(xoffset, yoffset);
}

void Viewport::ScrollCallback(GLFWwindow* _window, double _xoffset, double _yoffset)
{
    Camera::instance->ProcessMouseScroll(_yoffset);
}

Camera* Viewport::GetCamera()
{
    return m_camera;
}

void Viewport::MouseMovement(GolemEngine* _golemEngine)
{
    glfwGetCursorPos(_golemEngine->GetWindow(), &m_cursorX, &m_cursorY);
    std::cout << m_cursorX << " " << m_cursorY << std::endl;
    if (glfwGetKey(_golemEngine->GetWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        glfwSetInputMode(_golemEngine->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        MouseCallback(_golemEngine, m_cursorX, -m_cursorY);
    }
    else
    {
        m_firstMouse = true;
        glfwSetInputMode(_golemEngine->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}