#include "UI/Windows/viewport.h"

#include "Core/camera.h"
#include "golemEngine.h"
#include "Wrappers/graphicWrapper.h"
#include "Wrappers/windowWrapper.h"
#include "Resource/Rendering/texture.h"
#include "Resource/Rendering/mesh.h"
#include "Resource/sceneManager.h"
#include "Resource/tools.h"
#include "Inputs/inputManager.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Core/scene.h"
#include "vector4.h"
#include "imgui_internal.h"
#include "imgui.h"

bool g_isFromFileBrowser = false;

Viewport::Viewport(std::string _name)
    : Window(_name), m_lastX(0), m_lastY(0), m_yaw(0), m_pitch(0)
{}

Viewport::~Viewport() {}

void Viewport::Update()
{
    SetCamera(GolemEngine::GetCamera());

    ImGui::Begin(name.c_str(), nullptr, ImGuiWindowFlags_NoMove);   // To make the window not movable because otherwise mouse position won't work if out of window
    
    auto viewportOffset = ImGui::GetCursorPos();

    auto windowSize = ImGui::GetWindowSize();
    ImVec2 minBound = ImGui::GetWindowPos();

    minBound.x += viewportOffset.x;
    minBound.y += viewportOffset.y;

    ImVec2 maxBound = { minBound.x + windowSize.x, minBound.y + windowSize.y };
    m_viewportBounds[0] = { minBound.x, minBound.y };
    m_viewportBounds[1] = { maxBound.x, maxBound.y };

    auto [mx, my] = ImGui::GetMousePos();
    mx -= m_viewportBounds[0].x;
    my -= m_viewportBounds[0].y;

    Vector2 viewportSize = m_viewportBounds[1] - m_viewportBounds[0];
    my = viewportSize.y - my;

    int mouseX = (int)mx;
    int mouseY = (int)my;

    Texture pickingTex(WindowWrapper::GetScreenSize().x, WindowWrapper::GetScreenSize().y, GL_RED);

    if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y)
    {
        GraphicWrapper::AttachTexture(GL_RED, pickingTex.m_width, pickingTex.m_height, 1, pickingTex.id);

        int pixelData = GraphicWrapper::ReadPixel(1, mouseX, mouseY);
        //Log::Print("pixelID = %d", pixelData);

        if (pixelData != 126322567 && InputManager::IsButtonPressed(BUTTON_0))
        {
            //std::cout << "selected" << std::endl;
        }

        else if (pixelData == 126322567 && InputManager::IsButtonPressed(BUTTON_0))
        {
            //std::cout << "deselected" << std::endl;
        }
    }

    ImGui::Image((ImTextureID)GraphicWrapper::GetTextureId(), ImGui::GetContentRegionAvail());
    
    Vector4 windowDimensions(ImGui::GetWindowDockNode()->Pos.x, ImGui::GetWindowDockNode()->Size.x, ImGui::GetWindowDockNode()->Pos.y, ImGui::GetWindowDockNode()->Size.y);

    DragDropEvent();

    DragDropEvent();

    if (ImGui::IsWindowHovered() && InputManager::IsButtonPressed(BUTTON_1))
    {
        m_lastSpacePress = true;
        m_camera->ProcessKeyboardInput(GolemEngine::GetDeltaTime());
        ImGui::SetMouseCursor(ImGuiMouseCursor_None);
        // Update camera with mouse position
        m_camera->ProcessMouseMovement(InputManager::GetMouseWindowPos(), true, windowDimensions, ImGui::GetMousePos().x, ImGui::GetMousePos().y);
        // Update camera speed depending on scroll
        m_camera->ProcessMouseScroll(InputManager::GetMouseScroll());
        InputManager::SetMouseScroll(0.0f);     // Otherwise the camera will continue to change since GetMouseScroll value doesn't change bt has a value
        m_camera->ProcessMouseInput();
    }

    // Upon space key released
    if (m_lastSpacePress && !InputManager::IsButtonPressed(BUTTON_1))
    {
        m_lastSpacePress = false;
        m_camera->isFirstMouse = true;  // Important so the next time you move in the viewport, it doesn't teleport the camera to the cursor
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

    if (g_isFromFileBrowser && m_isDragging)
    {
        ImVec2 itemRectMin = ImGui::GetItemRectMin();
        ImVec2 itemRectMax = ImGui::GetItemRectMax();

        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("FileDrop"))
        {
            std::string droppedFilePath(static_cast<const char*>(payload->Data), payload->DataSize);
            //std::cout << "Drop in " << droppedFilePath.c_str() << std::endl;
            // TODO 
            SceneManager::GetCurrentScene()->AddNewModel(droppedFilePath);
            SceneManager::GetCurrentScene()->isObjectInit = true;
            m_isDragging = false;
            g_isFromFileBrowser = false;
        }
    }
}

Camera* Viewport::GetCamera()
{
    return m_camera;
}