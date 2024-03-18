#include "UI/Windows/viewport.h"

#include "Viewport/camera.h"
#include "golemEngine.h"
#include "Wrappers/graphicWrapper.h"
#include "Wrappers/windowWrapper.h"
#include "inputManager.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"


Viewport::Viewport(std::string _name)
    : Window(_name), m_lastX(0), m_lastY(0), m_yaw(0), m_pitch(0), m_firstMouse(true)
{
}

Viewport::~Viewport() {}

void Viewport::Update(GolemEngine* _golemEngine)
{
    SetCamera(GolemEngine::GetInstance()->GetCamera());

    GraphicWrapper::EnableDepth();

    ImGui::Begin(name.c_str());

    ImGui::Image((ImTextureID)GraphicWrapper::GetTextureId(), ImGui::GetContentRegionAvail());

    if (ImGui::IsWindowFocused() && InputManager::IsKeyPressed(KEY_SPACE))
    {
        glfwSetInputMode(_golemEngine->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        m_camera->ProcessKeyboardInput(_golemEngine->GetDeltaTime());
        // Update mouse offset x and y value
        InputManager::MousePositionCallback(_golemEngine->GetWindow(), ImGui::GetMousePos().x, ImGui::GetMousePos().y);
        // Use these offsets
        m_camera->ProcessMouseInput(InputManager::GetMouseOffsetX(), InputManager::GetMouseOffsetY(), true);
        m_camera->ProcessMouseScroll(InputManager::GetScrollOffsetY());
        // Mouse offset values of x and y are not 0 so if you don't set them to 0 (with the following two lines), if you still activate viewport movement,
        // the camera will move even if you don't move the mouse.
        InputManager::SetMouseOffsetX(0.0f);
        InputManager::SetMouseOffsetY(0.0f);
    }
    else
    {
        glfwSetInputMode(_golemEngine->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    ImGui::End();
}

void Viewport::SetCamera(Camera* _camera)
{
    m_camera = _camera;
}

Camera* Viewport::GetCamera()
{
    return m_camera;
}