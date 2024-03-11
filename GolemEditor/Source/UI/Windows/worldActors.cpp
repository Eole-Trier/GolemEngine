#include "UI/Windows/worldActors.h"

#include "golemEngine.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

WorldActors::WorldActors() {}

WorldActors::~WorldActors() {}

void WorldActors::Update(GolemEngine* _golemEngine, const char* _name)
{
	ImGui::Begin("World_Actors");
	ImGui::End();
}