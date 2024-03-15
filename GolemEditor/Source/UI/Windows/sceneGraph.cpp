#include "UI/Windows/sceneGraph.h"

#include "golemEngine.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"


SceneGraph::SceneGraph(std::string _name) 
	: Window(_name)
{
}

SceneGraph::~SceneGraph() {}

void SceneGraph::Update(GolemEngine* _golemEngine)
{
	ImGui::Begin(name.c_str());
	ImGui::End();
}