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
#include "Resource/sceneManager.h"

Inspector::Inspector(std::string _name)
	: Window(_name)
{
}

Inspector::~Inspector() {}

void Inspector::Update()
{
	ImGui::Begin(name.c_str());

	if (EditorUi::selectedGameObject)
	{
		DisplayType::DisplayField(EditorUi::selectedGameObject);
		DisplayType::AddComponentHandler(EditorUi::selectedGameObject);

		if (!SceneManager::GetCurrentScene()->terrains.empty())
		{
			for (int i = 0; i < SceneManager::GetCurrentScene()->terrains.size(); i++)
			{
				if (EditorUi::selectedGameObject->GetId() == SceneManager::GetCurrentScene()->terrains[i]->GetId())
				{
					// TODO : call GetComputeShadersData
				}
			}
		}
	}

	
	ImGui::End();
}


