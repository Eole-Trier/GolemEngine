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
#include "Viewport/scene.h"
#include "golemEngine.h"


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

    DragDropEvent();

    if (InputManager::IsKeyPressed(KEY_SPACE))
    {
        m_camera->ProcessKeyboardInput(_golemEngine->GetDeltaTime());
        // Update mouse offset x and y value
        InputManager::MousePositionCallback(_golemEngine->GetWindow(), ImGui::GetMousePos().x, ImGui::GetMousePos().y);
        // Use these offsets
        m_camera->ProcessMouseInput(InputManager::GetMouseOffsetX(), InputManager::GetMouseOffsetY(), true);
        // Mouse offset values of x and y are not 0 so if you don't set them to 0 (with the following two lines), if you still activate viewport movement,
        // the camera will move even if you don't move the mouse.
        InputManager::SetMouseOffsetX(0.0f);
        InputManager::SetMouseOffsetY(0.0f);
        m_camera->ProcessMouseScroll(InputManager::GetScrollOffsetY());
    }

    ImGui::End();

}

void Viewport::SetCamera(Camera* _camera)
{
    m_camera = _camera;
}

void Viewport::DragDropEvent()
{
    if (ImGui::BeginDragDropTarget())
    {
        m_isDragging = true;

        ImGui::EndDragDropTarget();
    }

    if (m_isDragging)
    {
        ImVec2 itemRectMin = ImGui::GetItemRectMin();
        ImVec2 itemRectMax = ImGui::GetItemRectMax();

        if (ImGui::IsMouseHoveringRect(itemRectMin, itemRectMax))
        {
            std::cout << "Dropping" << std::endl;
        }

        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("FileDrop"))
        {
            std::string droppedFilePath(static_cast<const char*>(payload->Data), payload->DataSize);
            std::cout << "Drop in " << droppedFilePath.c_str() << std::endl;
            // TODO 
            GolemEngine::GetInstance()->GetScene()->isInit = true;
            m_isDragging = false;
        }
    }
}

Camera* Viewport::GetCamera()
{
    return m_camera;
}