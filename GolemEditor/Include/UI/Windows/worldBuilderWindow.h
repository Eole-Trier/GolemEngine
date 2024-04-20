#pragma once

#include "UI/Windows/window.h"


class WorldBuilderWindow : public Window
{
private:
    bool m_showCreateTerrainPopup = false;

public:
    WorldBuilderWindow(std::string _name);
    ~WorldBuilderWindow();

    void Update() override;
};