#include "UI/Windows/worldBuilderWindow.h"

#include "golemEngine.h"
#include "WorldBuilder/worldBuilder.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

const std::string CREATE_TERRAIN_POPUP_MESSAGE = "Enter terrain dimensions";

void UpdateCreateTerrainPopup(bool* _isPopupOpen, int* _xSize, int* _zSize);


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
        m_isCreateTerrainPopupActive = true;
    }

    UpdateCreateTerrainPopup(&m_isCreateTerrainPopupActive, &v1, &v2);

    ImGui::End();
}

void UpdateCreateTerrainPopup(bool* _isPopupOpen, int* _xSize, int* _zSize)
{
    // Check if the popup should open and if true, open it
    if (*_isPopupOpen)
    {
        ImGui::OpenPopup("Specify new terrain dimensions");
    }

    // Popup content
    if (ImGui::BeginPopupModal("Specify new terrain dimensions", _isPopupOpen))
    {
        ImGui::Text(CREATE_TERRAIN_POPUP_MESSAGE.c_str());

        ImGui::InputInt("x ", _xSize, 0, 0);
        ImGui::InputInt("z ", _zSize, 0, 0);

        if (*_xSize > 0 && *_zSize > 0)    // Check if the user hasn't given negative or null values to the size of the terrain
        {
            if (ImGui::Button("OK"))
            {
                WorldBuilder::CreateTerrain(*_xSize, *_zSize);
                *_isPopupOpen = false;
                ImGui::CloseCurrentPopup();
            }
            
        }
        else
        {
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Warning: Values can't be negative or null.");
        }

        ImGui::EndPopup();
    }
}