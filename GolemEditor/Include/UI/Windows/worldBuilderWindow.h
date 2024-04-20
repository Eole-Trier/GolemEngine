#pragma once

#include "UI/Windows/window.h"


class WorldBuilderWindow : public Window
{
private:
    bool m_isCreateTerrainPopupActive = false;
    int v1 = 0, v2 = 0;

public:
    WorldBuilderWindow(std::string _name);
    ~WorldBuilderWindow();

    void Update() override;
};