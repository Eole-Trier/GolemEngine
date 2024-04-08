#include "Reflection/displayType.h"
#include "Reflection/classesManager.h"
#include "Resource/sceneManager.h"
#include "Components/Light/point.h"
#include "Components/Light/spot.h"
#include "Components/Light/directional.h"

const char* DisplayType::m_addComponentPopupId = "Components";
const char* DisplayType::m_addComponentButtonName = "Add Component";
Vector2 DisplayType::m_addComponentButtonSize = Vector2(450, 20);

void DisplayType::DisplayWithHashCode(size_t _hashCode, void* _object)
{
	ClassesManager::Display(_hashCode, _object);
}

void DisplayType::AddComponentHandler(GameObject* _gameObject)
{
	if (ImGui::Button(m_addComponentButtonName, ImVec2(m_addComponentButtonSize.x, m_addComponentButtonSize.y)))
		ImGui::OpenPopup(m_addComponentPopupId);

	if (ImGui::BeginPopupContextItem(m_addComponentPopupId))
	{
		if (ImGui::MenuItem("Point Light"))
		{
			if (SceneManager::GetCurrentScene()->GetPointLights().size() < SceneManager::GetCurrentScene()->GetMaxPointLights() && !_gameObject->GetComponent<PointLight>())
			{
				_gameObject->AddComponent(new PointLight);
			}
		}
		ImGui::EndPopup();
	}
	if (ImGui::BeginPopupContextItem(m_addComponentPopupId))
	{
		if (ImGui::MenuItem("Spot Light"))
		{
			if (SceneManager::GetCurrentScene()->GetSpotLights().size() < SceneManager::GetCurrentScene()->GetMaxSpotLights() && !_gameObject->GetComponent<SpotLight>())
			{
				_gameObject->AddComponent(new SpotLight);
			}
		}
		ImGui::EndPopup();
	}
	if (ImGui::BeginPopupContextItem(m_addComponentPopupId))
	{
		if (ImGui::MenuItem("Directional Light"))
		{
			if (SceneManager::GetCurrentScene()->GetDirectionalLights().size() < SceneManager::GetCurrentScene()->GetMaxDirectionalLights() && !_gameObject->GetComponent<DirectionalLight>())
			{
				_gameObject->AddComponent(new DirectionalLight);
			}
		}
		ImGui::EndPopup();
	}
}