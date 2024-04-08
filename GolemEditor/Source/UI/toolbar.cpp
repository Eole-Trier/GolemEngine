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
        if (ImGui::BeginMenu("Menu"))
        {
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Scenes"))
        {
            if (ImGui::MenuItem("Save scene"))
            {
                SceneManager::SaveScene();
            }

            if (ImGui::BeginMenu("Load scenes"))
            {
                
                for (int i = 0; i < SceneManager::GetSceneCount(); i++)
                {
                    if (SceneManager::GetScene(i)->name != SceneManager::GetCurrentScene()->name)
                    {
                        std::string sceneName = SceneManager::GetScene(i)->name;
                        if (ImGui::MenuItem(sceneName.c_str()))
                        {
                            SceneManager::LoadScene(i);
                        }
                    }
                }

                ImGui::EndMenu();
            }

            if (ImGui::MenuItem("Create scene"))
            {
                std::string sceneName = "scene_";
                sceneName.append(std::to_string(SceneManager::GetSceneCount()));
                SceneManager::CreateScene(sceneName);
            }
            
            ImGui::EndMenu();
        }
        
        
        
        ImGui::EndMenuBar();
    }
}
