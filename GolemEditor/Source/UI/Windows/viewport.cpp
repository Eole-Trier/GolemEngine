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


Viewport::Viewport()
    :
    m_lastX(0),
    m_lastY(0),
    m_yaw(0),
    m_pitch(0),
    m_firstMouse(true)
{}

Viewport::~Viewport() {}

void Viewport::Update(GolemEngine* _golemEngine, Camera* _camera, const char* _name)
{
    GraphicWrapper::EnableDepth();

    ImGui::Begin("Viewport");

    ImGui::Image((ImTextureID)GraphicWrapper::GetTextureId(), ImGui::GetContentRegionAvail());

    if (InputManager::IsKeyPressed(KEY_SPACE))
    {
        _camera->ProcessKeyboardInput(_golemEngine->GetDeltaTime());
        _camera->ProcessMouseInput(InputManager::GetMouseOffsetX(), InputManager::GetMouseOffsetY(), true);
        // Mouse offset values of x and y are not 0 so if you don't set them to 0 (with the following two lines), if you still activate viewport movement,
        // the camera will move even if you don't move the mouse.
        InputManager::SetMouseOffsetX(0.0f);
        InputManager::SetMouseOffsetY(0.0f);
        _camera->ProcessMouseScroll(InputManager::GetScrollOffsetY());
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