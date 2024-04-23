#include "UI/Windows/viewportToolsWindow.h"

#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"


ViewportToolsWindow::ViewportToolsWindow(std::string _name)
    : Window(_name)
{}

ViewportToolsWindow::~ViewportToolsWindow() {}

void ViewportToolsWindow::Update()
{
    ImGui::Begin(name.c_str());
    ImGui::Checkbox("Wirefram view", &isWireframViewActive);
    ImGui::End();
}