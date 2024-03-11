#include "UI/Windows/basicActors.h"

#include "golemEngine.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"


BasicActors::BasicActors() {}

BasicActors::~BasicActors() {}

void BasicActors::Update(GolemEngine* _golemEngine, const char* _name)
{
	ImGui::Begin("Basic_Actors");
	ImGui::End();
}