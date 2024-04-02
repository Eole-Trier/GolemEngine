#include "UI/Windows/toolBar.h"

#include "golemEngine.h"
#include "Inputs/inputManager.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

ToolBar::ToolBar(std::string _name)
	: Window(_name)
{
}

ToolBar::~ToolBar() {}

void ToolBar::Update()
{
	ImGui::Begin(name.c_str());
	ImGui::End();
}