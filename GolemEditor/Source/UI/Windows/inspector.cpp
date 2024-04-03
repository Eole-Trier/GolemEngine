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
#include "Components/Light/point.h"
#include "Components/Light/spot.h"
#include "Components/Light/directional.h"
#include "Resource/sceneManager.h"

Inspector::Inspector(std::string _name)
	: Window(_name)
{
	m_addComponentPopupId = "Components";
	m_addComponentButtonName = "Add Component";
	m_addComponentButtonSize = Vector2(450, 20);
}

Inspector::~Inspector() {}

void Inspector::Update()
{
	ImGui::Begin(name.c_str());

	if (EditorUi::selected)
	{
		DisplayType::DisplayField(EditorUi::selected);
		AddComponentHandler();
		
	}
	ImGui::End();
}

void Inspector::AddComponentHandler()
{
	if (ImGui::Button(m_addComponentButtonName, ImVec2(m_addComponentButtonSize.x, m_addComponentButtonSize.y)))
		ImGui::OpenPopup(m_addComponentPopupId);

	if (ImGui::BeginPopupContextItem(m_addComponentPopupId))
	{
		if (ImGui::MenuItem("Point Light"))
		{
			if (SceneManager::GetCurrentScene()->GetPointLights().size() < SceneManager::GetCurrentScene()->GetMaxPointLights() && !EditorUi::selected->GetComponent<PointLight>())
			{
				PointLight* pL = new PointLight;
				EditorUi::selected->AddComponent(pL);
			}
			else
			{
				Log::Print("The PointLight will not be Created. A GameObject can only have one PointLight. PointLights limit : %d", SceneManager::GetCurrentScene()->GetMaxPointLights());
			}
		}
		ImGui::EndPopup();
	}
	if (ImGui::BeginPopupContextItem(m_addComponentPopupId))
	{
		if (ImGui::MenuItem("Spot Light"))
		{
			if (SceneManager::GetCurrentScene()->GetSpotLights().size() < SceneManager::GetCurrentScene()->GetMaxSpotLights() && !EditorUi::selected->GetComponent<SpotLight>())
			{
				SpotLight* pL = new SpotLight;
				EditorUi::selected->AddComponent(pL);
			}
			else
			{
				Log::Print("The SpotLight will not be Created. A GameObject can only have one SpotLight. SpotLights limit : %d", SceneManager::GetCurrentScene()->GetMaxSpotLights());
			}
		}
		ImGui::EndPopup();
	}
	if (ImGui::BeginPopupContextItem(m_addComponentPopupId))
	{
		if (ImGui::MenuItem("Directional Light"))
		{
			if (SceneManager::GetCurrentScene()->GetDirectionalLights().size() < SceneManager::GetCurrentScene()->GetMaxDirectionalLights() && !EditorUi::selected->GetComponent<DirectionalLight>())
			{
				DirectionalLight* pL = new DirectionalLight;
				EditorUi::selected->AddComponent(pL);
			}
			else
			{
				Log::Print("The DirectionalLight will not be Created. A GameObject can only have one DirectionalLight. DirectionalLights limit : %d", SceneManager::GetCurrentScene()->GetMaxDirectionalLights());
			}
		}
		ImGui::EndPopup();
	}
}

