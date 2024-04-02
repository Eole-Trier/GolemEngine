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
#include "vector2.h"
#include "vector4.h"


Viewport::Viewport(std::string _name)
    : Window(_name), m_lastX(0), m_lastY(0), m_yaw(0), m_pitch(0)
{}

Viewport::~Viewport() {}

void Viewport::Update(GolemEngine* _golemEngine)
{
    SetCamera(GolemEngine::GetInstance()->GetCamera());

    GraphicWrapper::CreateFramebuffer(GL_RED, WindowWrapper::GetScreenSize().x, WindowWrapper::GetScreenSize().y);

    ImGui::Begin(name.c_str(), nullptr, ImGuiWindowFlags_NoMove);   // To make the window not movable because otherwise mouse position won't work if out of window
    
    auto viewportOffset = ImGui::GetCursorPos();

    auto [mx, my] = ImGui::GetMousePos();
    mx -= m_viewportBounds[0].x;
    my -= m_viewportBounds[0].y;

    Vector2 viewportSize = m_viewportBounds[1] - m_viewportBounds[0];
    my = viewportSize.y - my;

    int mouseX = (int)mx;
    int mouseY = (int)my;

    if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y)
    {
        int pixelData = GraphicWrapper::ReadPixel(1, mouseX, mouseY);
        Log::Print("Pixel data = %d", pixelData);
    }

    ImGui::Image((ImTextureID)GraphicWrapper::GetTextureId(), ImGui::GetContentRegionAvail());

    auto windowSize = ImGui::GetWindowSize();
    ImVec2 minBound = ImGui::GetWindowPos();
    minBound.x += viewportOffset.x;
    minBound.y += viewportOffset.y;

    ImVec2 maxBound = { minBound.x + windowSize.x, minBound.y + windowSize.y };
    m_viewportBounds[0] = { minBound.x, minBound.y };
    m_viewportBounds[1] = { maxBound.x, maxBound.y };
    
    Vector4 windowDimensions(ImGui::GetWindowDockNode()->Pos.x, ImGui::GetWindowDockNode()->Size.x, ImGui::GetWindowDockNode()->Pos.y, ImGui::GetWindowDockNode()->Size.y);
    //std::cout << ImGui::GetWindowDockNode()->Pos.x << std::endl;
    //std::cout << ImGui::GetMousePos().x << " " << ImGui::GetMousePos().y << std::endl;

    if (ImGui::IsWindowHovered() && InputManager::IsButtonPressed(BUTTON_1))
    {
        m_lastSpacePress = true;
        m_camera->ProcessKeyboardInput(_golemEngine->GetDeltaTime());
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

Camera* Viewport::GetCamera()
{
    return m_camera;
}