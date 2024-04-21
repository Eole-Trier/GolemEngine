#include "UI/Windows/worldBuilderWindow.h"

#include "golemEngine.h"
#include "WorldBuilder/worldBuilder.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "Resource/tools.h"

const std::string CREATE_TERRAIN_POPUP_TITLE = "Specify new terrain dimensions";
const std::string CREATE_TERRAIN_POPUP_MESSAGE = "Enter terrain dimensions";


void UpdateCreateTerrainPopup(bool* _isPopupOpen, int* _xResolution, int* _zResolution, float* _generationScale);


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

    UpdateCreateTerrainPopup(&m_isCreateTerrainPopupActive, &m_newTerrainResolutionX, &m_newTerrainResolutionZ, &m_newTerrainGenerationScale);

    if (ImGui::Button("Create new noisemap terrain"))
    {
        WorldBuilder::CreateTerrainNoisemap(Tools::FindFile("heightmap.png").c_str());
    }


    ImGui::End();
}

void UpdateCreateTerrainPopup(bool* _isPopupOpen, int* _xResolution, int* _zResolution, float* _generationScale)
{
    // Check if the popup should open and if true, open it
    if (*_isPopupOpen)
    {
        ImGui::OpenPopup(CREATE_TERRAIN_POPUP_TITLE.c_str());
    }
    
    // Popup content
    if (ImGui::BeginPopupModal(CREATE_TERRAIN_POPUP_TITLE.c_str(), _isPopupOpen))
    {
        ImGui::Text(CREATE_TERRAIN_POPUP_MESSAGE.c_str());

        ImGui::InputInt("x resolution", _xResolution, 0, 0);
        ImGui::InputInt("z resolution", _zResolution, 0, 0);
        ImGui::InputFloat("generation scale", _generationScale, 0, 0);

        bool isUserInputValid = true;
        if (*_xResolution < 2 || *_zResolution < 2)    // Minimum terrain dimension
        {
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Warning: Minimum terrain resolution are 2 by 2.");
            isUserInputValid = false;
        }
        if (*_generationScale == 0.0f)    // Minimum terrain dimension
        {
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Warning: Terrain generation scale can't be 0.");
            isUserInputValid = false;
        }
        
        if (isUserInputValid && ImGui::Button("OK"))
        {
            WorldBuilder::CreateTerrain(*_xResolution, *_zResolution, *_generationScale);
            *_isPopupOpen = false;
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}