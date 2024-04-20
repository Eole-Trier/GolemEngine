#include "UI/Windows/worldBuilderWindow.h"

#include "golemEngine.h"
#include "WorldBuilder/worldBuilder.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

const std::string CREATE_TERRAIN_POPUP_MESSAGE = "Enter terrain dimensions";


WorldBuilderWindow::WorldBuilderWindow(std::string _name) 
    : Window(_name)
{}

WorldBuilderWindow::~WorldBuilderWindow() {}

void WorldBuilderWindow::Update()
{
    ImGui::Begin(name.c_str());

    // Button to show the popup
    if (ImGui::Button("Create new terrain"))
    {
        m_showCreateTerrainPopup = true;
    }

    // Check if the popup should be shown
    if (m_showCreateTerrainPopup)
    {
        ImGui::OpenPopup("Specify_terrain_values");
    }

    // Show the popup
    if (ImGui::BeginPopupModal("Specify_terrain_values", &m_showCreateTerrainPopup))
    {
        ImGui::Text(CREATE_TERRAIN_POPUP_MESSAGE.c_str());

        ImGui::EndPopup();
    }
    
    ImGui::End();
}