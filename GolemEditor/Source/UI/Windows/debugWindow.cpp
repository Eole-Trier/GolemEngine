#include "UI/Windows/debugWindow.h"

#include "golemEngine.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"


DebugWindow::DebugWindow() {}

DebugWindow::~DebugWindow() {}

void DebugWindow::Update(GolemEngine* _golemEngine, const char* _name)
{
	ImGui::Begin("Debug");
	ImGui::Text("deltaTime: %f", _golemEngine->GetDeltaTime());
	ImGui::Text("time: %f", _golemEngine->GetTime());
	ImGui::End();
}