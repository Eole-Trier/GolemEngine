#include "UI/Windows/debugWindow.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "golemEngine.h"

DebugWindow::DebugWindow() {}

DebugWindow::~DebugWindow() {}

void DebugWindow::Update(GolemEngine* _golemEngine)
{
	ImGui::Begin("Debug");
	ImGui::Text("deltaTime: %f", _golemEngine->GetDeltaTime());
	ImGui::Text("time: %f", _golemEngine->GetTime());
	ImGui::End();
}