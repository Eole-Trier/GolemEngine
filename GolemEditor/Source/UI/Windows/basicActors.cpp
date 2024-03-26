#include "UI/Windows/basicActors.h"

#include "Core/gameobject.h"
#include "golemEngine.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "Reflection/refl.hpp"


BasicActors::BasicActors(std::string _name) 
	: Window(_name)
{}

BasicActors::~BasicActors() {}

void BasicActors::Update(GolemEngine* _golemEngine)
{
	ImGui::Begin(name.c_str());

	ImGui::End();
}