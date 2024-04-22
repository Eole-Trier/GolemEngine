#pragma once

#include <vector2.h>
#include <vector3.h>

#include "UI/Windows/window.h"


class WorldBuilderWindow : public Window
{
private:
#pragma region Create Terrain Variables
    bool m_isCreateDefaultTerrainPopupActive = false;
    int m_newDefaultTerrainResolutionX = 0;
    int m_newDefaultTerrainResolutionZ = 0;
    Vector2 m_newDefaultTerrainSize = {1.0f, 1.0f};
#pragma endregion Create Terrain Variables
    
public:
    WorldBuilderWindow(std::string _name);
    ~WorldBuilderWindow();

    void Update() override;
    void UpdateCreateDefaultTerrainPopup(bool _isPopupOpen, int _xResolution, int _zResolution, Vector2 _size);
};