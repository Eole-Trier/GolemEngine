#include "UI/Windows/debugWindow.h"

#include "golemEngine.h"
#include "inputManager.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"


DebugWindow::DebugWindow(std::string _name)
	: Window(_name)
{
}

DebugWindow::~DebugWindow() {}

void DebugWindow::Update(GolemEngine* _golemEngine)
{
	ImGui::Begin(name.c_str());
	ImGui::Text("deltaTime: %f", _golemEngine->GetDeltaTime());
	ImGui::Text("time: %f", _golemEngine->GetTime());
	ImGui::Text("Screen size: %.0f %.0f", WindowWrapper::GetScreenSize().x, WindowWrapper::GetScreenSize().y);
	ImGui::Text("Mouse position relative to window: %.0f %.0f", InputManager::GetMouseWindowPos().x, InputManager::GetMouseWindowPos().y);
	ImGui::Text("Mouse position relative to screen: %.0f %.0f", ImGui::GetMousePos().x, ImGui::GetMousePos().y);
	ImGui::End();
}