#include "UI/Windows/inspector.h"

#include "Core/gameobject.h"
#include "golemEngine.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "Reflection/refl.hpp"


Inspector::Inspector(std::string _name)
	: Window(_name)
{}


Inspector::~Inspector() {}

void Inspector::Update(GolemEngine* _golemEngine)
{
	ImGui::Begin(name.c_str());

	refl::descriptor::type_descriptor<GameObject> a = refl::reflect<GameObject>();

	refl::util::for_each(a.members, [&]<typename T>(const T) {


		std::cout << typeid(T::value_type).name() << std::endl;
	});

	ImGui::End();
}