#include "Reflection/displayType.h"
#include "Reflection/classesManager.h"
#include "Resource/sceneManager.h"
#include "..\..\Include\Components\Light\pointLight.h"
#include "..\..\Include\Components\Light\spotLight.h"
#include "..\..\Include\Components\Light\directionalLight.h"

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

	std::vector<std::string>&& classes = ClassesManager::GetComponents();

	for (const std::string& name : classes)
	{
		if (ImGui::BeginPopupContextItem(m_addComponentPopupId))
		{
			if (ImGui::MenuItem(name.c_str()))
			{
				if (!_gameObject->HasComponent(name))
				{
					Component* obj = static_cast<Component*>(ClassesManager::Create(name));
					if (obj)
					{
						_gameObject->AddComponent(obj);
						obj->Begin();
					}
				}
			}

			ImGui::EndPopup();
		}
	}
}