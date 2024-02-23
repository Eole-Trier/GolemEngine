#include "UI/debugWindow.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "UI/engineWindow.h"

DebugWindow::DebugWindow() {}

DebugWindow::~DebugWindow() {}

void DebugWindow::Render(EngineWindow* _engineWindow)
{
	ImGui::Begin("Debug");
	ImGui::Text("deltaTime: %f", _engineWindow->deltaTime);
	ImGui::Text("time: %f", _engineWindow->time);
	ImGui::End();
}