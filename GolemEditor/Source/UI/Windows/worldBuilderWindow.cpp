#include "UI/Windows/worldBuilderWindow.h"

#include "golemEngine.h"
#include "WorldBuilder/worldBuilder.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "Utils/tools.h"

const std::string CREATE_DEFAULT_TERRAIN_POPUP_TITLE = "Specify new terrain dimensions";
const std::string CREATE_DEFAULT_TERRAIN_POPUP_MESSAGE = "Enter terrain dimensions";


WorldBuilderWindow::WorldBuilderWindow(std::string _name) 
    : Window(_name)
{}

WorldBuilderWindow::~WorldBuilderWindow() {}


void WorldBuilderWindow::Update()
{
    ImGui::Begin(name.c_str());

    if (ImGui::Button("Create new terrain"))
    {
        m_isCreateDefaultTerrainPopupActive = true;
    }

    if (m_isCreateDefaultTerrainPopupActive)
    {
        UpdateCreateDefaultTerrainPopup(m_newDefaultTerrainResolutionX, m_newDefaultTerrainResolutionZ);
    }

    if (ImGui::Button("Create new noisemap terrain"))
    {
        m_isCreateDefaultNoisemapTerrainPopupActive = true;
    }

    if (m_isCreateDefaultNoisemapTerrainPopupActive)
    {
        UpdateCreateDefaultNoisemapeTerrainPopup();
    }

    ImGui::End();
}

void WorldBuilderWindow::UpdateCreateDefaultTerrainPopup(int& _xResolution, int& _zResolution)
{
    ImGui::OpenPopup(CREATE_DEFAULT_TERRAIN_POPUP_TITLE.c_str());
    
    // Popup content
    if (ImGui::BeginPopupModal(CREATE_DEFAULT_TERRAIN_POPUP_TITLE.c_str()))
    {
        ImGui::Text(CREATE_DEFAULT_TERRAIN_POPUP_MESSAGE.c_str());

        // Set terrain dimensions. Resolution are for the number of vertices inside the terrain
        ImGui::InputInt("x resolution", &_xResolution, 0, 0);
        ImGui::InputInt("z resolution", &_zResolution, 0, 0);

        // Check if user inputs are valid
        bool isUserInputValid = true;
        if (_xResolution < 2 || _zResolution < 2)    // Minimum terrain dimension
        {
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Warning: Minimum terrain resolution are 2 by 2.");
            isUserInputValid = false;
        }

        // Create terrain on valid input and "OK" button pressed
        if (isUserInputValid && ImGui::Button("OK"))
        {
            WorldBuilder::CreateDefaultTerrain(_xResolution, _zResolution);
            m_isCreateDefaultTerrainPopupActive = false;
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}

void WorldBuilderWindow::UpdateCreateDefaultNoisemapeTerrainPopup()
{
    ImGui::OpenPopup(CREATE_DEFAULT_TERRAIN_POPUP_TITLE.c_str());
    
    // Popup content
    if (ImGui::BeginPopupModal(CREATE_DEFAULT_TERRAIN_POPUP_TITLE.c_str()))
    {
        ImGui::Text(CREATE_DEFAULT_TERRAIN_POPUP_MESSAGE.c_str());

        
        // Check if user inputs are valid
        bool isUserInputValid = true;
        
        // Create terrain on valid input and "OK" button pressed
        if (isUserInputValid && ImGui::Button("OK"))
        {
            WorldBuilder::CreateNoisemapTerrain(Tools::FindFile("heightmap.png").c_str());
            m_isCreateDefaultNoisemapTerrainPopupActive = false;
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}