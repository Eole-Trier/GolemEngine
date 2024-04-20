#pragma once

#include <vector3.h>

#include "UI/Windows/window.h"


class WorldBuilderWindow : public Window
{
private:
#pragma region Create Terrain Variables
    bool m_isCreateTerrainPopupActive = false;
    int m_newTerrainResolutionX = 0;
    int m_newTerrainResolutionZ = 0;
    float m_newTerrainGenerationScale = 1.0f;
#pragma endregion Create Terrain Variables
    
public:
    WorldBuilderWindow(std::string _name);
    ~WorldBuilderWindow();

    void Update() override;
};