#include "UI/Windows/worldBuilderWindow.h"

#include "golemEngine.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

WorldBuilderWindow::WorldBuilderWindow(std::string _name) 
    : Window(_name)
{}

WorldBuilderWindow::~WorldBuilderWindow() {}

void WorldBuilderWindow::Update()
{
    ImGui::Begin(name.c_str());
    
    ImGui::End();
}