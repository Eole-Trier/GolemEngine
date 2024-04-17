#pragma once

#include "UI/Windows/window.h"


class WorldBuilderWindow : public Window
{
public:
    WorldBuilderWindow(std::string _name);
    ~WorldBuilderWindow();

    void Update() override;
};