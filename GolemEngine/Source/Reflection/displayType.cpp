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
				PointLight* pL = new PointLight;
				_gameObject->AddComponent(pL);
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
			if (SceneManager::GetCurrentScene()->GetSpotLights().size() < SceneManager::GetCurrentScene()->GetMaxSpotLights() && !_gameObject->GetComponent<SpotLight>())
			{
				SpotLight* pL = new SpotLight;
				_gameObject->AddComponent(pL);
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
			if (SceneManager::GetCurrentScene()->GetDirectionalLights().size() < SceneManager::GetCurrentScene()->GetMaxDirectionalLights() && !_gameObject->GetComponent<DirectionalLight>())
			{
				DirectionalLight* pL = new DirectionalLight;
				_gameObject->AddComponent(pL);
			}
			else
			{
				Log::Print("The DirectionalLight will not be Created. A GameObject can only have one DirectionalLight. DirectionalLights limit : %d", SceneManager::GetCurrentScene()->GetMaxDirectionalLights());
			}
		}
		ImGui::EndPopup();
	}
}