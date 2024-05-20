#include "UI/Windows/playScene.h"
#include "Wrappers/graphicWrapper.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "golemEngine.h"

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
        ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 20);
        if (ImGui::SmallButton("X"))
        {
            g_isPlayTesting = false;
            //GolemEngine::SetGameMode();
        }
        ImGui::SetCursorPosX(0);
        ImGui::Image((ImTextureID)GraphicWrapper::GetPlaySceneId(), ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));

        ImGui::End();
        ImGui::PopStyleColor();
    }
}