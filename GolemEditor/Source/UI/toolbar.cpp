#include "UI/toolbar.h"

#include "Resource/sceneManager.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"


void Toolbar::Update()
{
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Save Scene"))
        {
            SceneManager::SaveScene();
            ImGui::EndMenu();
        }
        
        ImGui::EndMenuBar();
    }
}
