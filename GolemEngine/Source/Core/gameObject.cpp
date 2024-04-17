#include "Core/gameObject.h"
#include "Components/component.h"
#include "golemEngine.h"
#include "Resource/sceneManager.h"
#include "ImGuizmo.h"
#include "golemEngine.h"
#include "MathsLib/utils.h"

GameObject::GameObject()
	: m_selected(false)
{
	name = "New GameObject";
	m_id = SceneManager::GetCurrentScene()->GetGameObjects().size();
	AddComponent(new Transform);
	transform = GetComponent<Transform>();
	SceneManager::GetCurrentScene()->AddGameObject(this);
}

GameObject::GameObject(const std::string& _name, Transform* _transform) 
	: name(_name), m_selected(false)
{
	m_id = SceneManager::GetCurrentScene()->GetGameObjects().size();
	AddComponent(_transform);
	transform = GetComponent<Transform>();
	SceneManager::GetCurrentScene()->AddGameObject(this);
}

GameObject::~GameObject() 
{
	SceneManager::GetCurrentScene()->RemoveGameObject(this);
	DeleteAllComponents();
}

std::string GameObject::GetName()
{
	return name;
}

size_t GameObject::GetId()
{
	return m_id;
}

void GameObject::SetId(size_t _id)
{
	m_id = _id;
}

void GameObject::DeleteTransform(Transform* _t)
{
	_t->GetParent()->RemoveChild(_t);

	for (Transform* go : _t->GetChildren())
	{
		delete go->owner;
	}
}

void GameObject::DeleteLight(Light* _l)
{
	SceneManager::GetCurrentScene()->DeleteLight(_l);
}

void GameObject::RemoveComponent(Component* _c)
{
	delete _c;
	std::erase(m_components, _c);
}

void GameObject::DeleteAllComponents()
{
	for (Component* c : m_components)
	{
		delete c;
	}
	for (Component* c : m_components)
	{
		std::erase(m_components, c);
	}
}

void GameObject::DisplayGizmo()
{
	ImGuizmo::SetOrthographic(false);
	ImGuizmo::Enable(true);
	ImGuizmo::SetDrawlist();
	ImGuizmo::BeginFrame();

	float windowWidth = (float)ImGui::GetWindowWidth();
	float windowHeight = (float)ImGui::GetWindowHeight();
	ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

	auto camera = GolemEngine::GetCamera();
	Matrix4 cameraProjection = Matrix4::Projection(DegToRad(camera->GetZoom()), windowWidth / windowHeight, camera->Camera::GetNear(), camera->Camera::GetFar());
	Matrix4 cameraView = camera->GetViewMatrix().Inverse();
	Matrix4 transformTest = transform->GetGlobalModel();

	ImGuizmo::Manipulate(&cameraView.data[0][0], &cameraProjection.data[0][0], ImGuizmo::OPERATION::TRANSLATE, ImGuizmo::WORLD, &transformTest.data[0][0], NULL, NULL);
}

