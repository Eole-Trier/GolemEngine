#include "UI/Windows/viewport.h"

#include "Viewport/camera.h"
#include "golemEngine.h"
#include "Wrappers/graphicWrapper.h"
#include "Wrappers/windowWrapper.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

Camera* Viewport::m_camera = new Camera(Vector3(0.0f, 0.0f, 3.0f));

Viewport::Viewport()
    :
    m_lastX(0),
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
        Camera::instance->ProcessInput(WindowWrapper::GetWindow(), _golemEngine->GetDeltaTime());
    }

    ImGui::End();
}

Camera* Viewport::GetCamera()
{
    return m_camera;
}