#include "UI/Windows/playScene.h"
#include "Wrappers/graphicWrapper.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "imgui.h"
#include "golemEngine.h"
#include "Inputs/inputManager.h"

bool g_isPlayTesting = false;

PlayScene::PlayScene(std::string _name)
	:Window(_name)
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
    if (g_isPlayTesting)
    {
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 1, 0, 1));
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar;

        ImGui::Begin("Playing", nullptr, window_flags);
        ImGui::SetMouseCursor(ImGuiMouseCursor_None);
        GolemEngine::GetPlayerCamera()->MouseMovement(ImGui::GetMousePos().x, ImGui::GetMousePos().y, m_lastMousepos.x, m_lastMousepos.y);
        if (ImGui::SmallButton("X") || InputManager::IsKeyPressed(KEY_ESCAPE))
        {
            g_isPlayTesting = false;
            GolemEngine::StopGameMode();
        }

        ImGui::Image((ImTextureID)GraphicWrapper::GetPlaySceneId(), ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));

        ImGui::End();
        ImGui::PopStyleColor();
    }
    m_lastMousepos = Vector2(ImGui::GetMousePos().x, ImGui::GetMousePos().y);
}