#include "UI/Windows/debugWindow.h"

#include "golemEngine.h"
#include "Inputs/inputManager.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"


DebugWindow::DebugWindow(std::string _name)
	: Window(_name)
{
}

DebugWindow::~DebugWindow() {}

void DebugWindow::Update()
{
	ImGui::Begin(name.c_str());
	ImGui::Text("deltaTime: %f", GolemEngine::GetDeltaTime());
	ImGui::Text("time: %f", GolemEngine::GetTime());
	ImGui::Text("fps: %.0f", 1.0f / GolemEngine::GetDeltaTime());
	ImGui::Text("Screen size: %.0f %.0f", WindowWrapper::GetScreenSize().x, WindowWrapper::GetScreenSize().y);
	ImGui::Text("Mouse position relative to window: %.0f %.0f", InputManager::GetMouseWindowPos().x, InputManager::GetMouseWindowPos().y);
	ImGui::Text("Mouse position relative to screen: %.0f %.0f", ImGui::GetMousePos().x, ImGui::GetMousePos().y);
	ImGui::Text("Camera position: %.2f %.2f %.2f", GolemEngine::GetCamera()->position.x, GolemEngine::GetCamera()->position.y, GolemEngine::GetCamera()->position.z);
	ImGui::End();
}