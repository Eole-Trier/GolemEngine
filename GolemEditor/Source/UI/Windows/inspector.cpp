#include "UI/Windows/inspector.h"

#include "Core/gameobject.h"
#include "golemEngine.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "Refl/refl.hpp"
#include "UI/editorUi.h"
#include "Reflection/displayType.h"


Inspector::Inspector(std::string _name)
	: Window(_name)
{
	addComponentButtonSize = Vector2(400, 20);
}

Inspector::~Inspector() {}

void Inspector::Update(GolemEngine* _golemEngine)
{
	ImGui::Begin(name.c_str());

	if (EditorUi::selected != nullptr)
	{
		DisplayType::DisplayField(EditorUi::selected);
		
		if (ImGui::Button("Add Component", ImVec2(addComponentButtonSize.x, addComponentButtonSize.y)))
		{

		}
	}
	ImGui::End();
}