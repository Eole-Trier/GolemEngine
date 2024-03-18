#include "UI/Windows/sceneGraph.h"

#include "golemEngine.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

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

	DisplayObjects(_golemEngine->GetScene()->GetWorld());

	ImGui::End();
}

void SceneGraph::DisplayObjects(GameObject* _gameObject)
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
	if (ImGui::TreeNodeEx(name, flags))
	{
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
				GameObject* gameObject = *(GameObject**)dragged->Data;

				// to do reparent
				_gameObject->transform->AddChild(gameObject->transform);
			}

			ImGui::EndDragDropTarget();
		}

		if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
		{
			m_selected = _gameObject;
		}

		for (Transform* transform : children)
		{
			DisplayObjects(transform->owner);
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
