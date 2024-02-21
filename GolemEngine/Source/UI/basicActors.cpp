#include "UI/basicActors.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

BasicActors::BasicActors() {}

BasicActors::~BasicActors() {}

void BasicActors::Render()
{
	ImGui::Begin("Basic_Actors");
	ImGui::End();
}