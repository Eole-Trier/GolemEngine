#include "UI/Windows/sceneGraph.h"

#include "golemEngine.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "imgui_stdlib.h"

#include "Core/gameobject.h"
#include "Core/transform.h"


SceneGraph::SceneGraph(std::string _name) 
	: Window(_name)
{
}

SceneGraph::~SceneGraph() {}

void SceneGraph::Update(GolemEngine* _golemEngine)
{
	ImGui::Begin(name.c_str());

	DisplayObjects(_golemEngine, _golemEngine->GetScene()->GetWorld());

	ImGui::End();
}

void SceneGraph::DisplayObjects(GolemEngine* _golemEngine, GameObject* _gameObject)
{
	const std::vector<Transform*>& children = _gameObject->transform->GetChildren();
	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanFullWidth;

	if (children.size() == 0)
	{
		flags |= ImGuiTreeNodeFlags_Leaf;
	}

	if (_gameObject == m_selected)
	{
		flags |= ImGuiTreeNodeFlags_Selected;
	}

	std::string n = _gameObject->GetName();
	const char* name = n.c_str();

	if (m_renaming == _gameObject)
	{
		name = "##input";
	}

	if (ImGui::TreeNodeEx(name, flags) && _gameObject)
	{
		if (m_renaming == _gameObject)
		{
			ImGui::SameLine();
			ImGui::SetKeyboardFocusHere();
			if (ImGui::InputText("##input", &_gameObject->name, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_EscapeClearsAll))
			{
				m_renaming = nullptr;
			}
		}
		else
		{
			// Rename popup
			if (ImGui::BeginPopupContextItem("Manage Gameobjects"))
			{
				if (ImGui::MenuItem("Rename"))
				{
					m_renaming = _gameObject;
				}
				ImGui::EndPopup();
			}

			// Create popup
			if (ImGui::BeginPopupContextItem("Manage Gameobjects"))
			{
				if (ImGui::MenuItem("Create"))
				{
					_golemEngine->GetScene()->CreateGameObject(_gameObject);
				}
				ImGui::EndPopup();
			}

			// Delete popup
			if (ImGui::BeginPopupContextItem("Manage Gameobjects"))
			{
				if (ImGui::MenuItem("Delete") && _gameObject != _golemEngine->GetScene()->GetWorld())
				{
					_golemEngine->GetScene()->DeleteGameObject(_gameObject);
				}
				ImGui::EndPopup();
			}

			if (ImGui::BeginDragDropSource())
			{
				ImGui::SetDragDropPayload("Golem", &_gameObject, sizeof(_gameObject));

				ImGui::Text("%s", name); 
				ImGui::EndDragDropSource();
			}

			if (ImGui::BeginDragDropTarget())
			{
				const ImGuiPayload* dragged = ImGui::AcceptDragDropPayload("Golem");

				if (dragged)
				{
					GameObject* gameObjectDragged = *(GameObject**)dragged->Data;

					if (!gameObjectDragged->transform->IsAParentOf(_gameObject->transform) && gameObjectDragged != _golemEngine->GetScene()->GetWorld())
					{
						gameObjectDragged->transform->SetParent(_gameObject->transform);
					}
				}

				ImGui::EndDragDropTarget();
			}

			if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
			{
				m_selected = _gameObject;
			}
		}

		for (Transform* transform : children)
		{
			DisplayObjects(_golemEngine, transform->owner);
		}

		ImGui::TreePop();
	}
	else
	{
		if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
		{
			m_selected = _gameObject;
		}
	}
}
