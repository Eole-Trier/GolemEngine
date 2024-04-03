#include "Core/gameObject.h"
#include "Components/component.h"
#include "golemEngine.h"
#include "Resource/sceneManager.h"

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
	DeleteAllComponents();
}

void GameObject::Update()
{
	for (auto& component : m_components)
	{
		//component->Update();
	}
}

std::string GameObject::GetName()
{
	return name;
}

int GameObject::GetId()
{
	return m_id;
}

void GameObject::DeleteTransform(Transform* _t)
{
	_t->GetParent()->RemoveChild(_t);

	for (Transform* go : _t->GetChildren())
	{
		SceneManager::GetCurrentScene()->DeleteGameObject(go->owner);
	}
}

void GameObject::DeleteLight(Light* _l)
{
	SceneManager::GetCurrentScene()->DeleteLight(_l);
}

void GameObject::RemoveComponent(Component* _c)
{
	std::erase(m_components, _c);
	delete _c;
}

void GameObject::DeleteAllComponents()
{
	for (Component* c : m_components)
	{
		RemoveComponent(c);
	}
}

