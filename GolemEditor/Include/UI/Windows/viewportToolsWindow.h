#pragma once

#include "UI/Windows/window.h"


class ViewportToolsWindow : public Window
{
public:
    bool isWireframeViewActive = false;
    
public:
    ViewportToolsWindow(std::string _name);
    ~ViewportToolsWindow();

    void Update() override;
};