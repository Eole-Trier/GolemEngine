#include "UI/toolbar.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"


void Toolbar::Update()
{
    if (ImGui::BeginMenuBar())
    {
        // Add your toolbar items here
        if (ImGui::BeginMenu("Save Scene"))
        {
            // Add menu items here
            ImGui::EndMenu();
        }
        // Add more menus if needed
        ImGui::EndMenuBar();
    }
}
