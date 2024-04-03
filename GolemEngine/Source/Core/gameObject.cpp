#include "Core/gameObject.h"
#include "Components/component.h"
#include "golemEngine.h"
#include "Resource/sceneManager.h"

GameObject::GameObject(const std::string& _name, Transform* _transform) 
	: name(_name), m_selected(false)
{
	AddComponent(_transform);
	transform = GetComponent<Transform>();

	std::cout << guid.ToString() << std::endl;
}

GameObject::~GameObject() {}

void GameObject::Update()
{
	for (auto& component : m_components)
	{
		//component->Update();
	}
}

void GameObject::DisplayInformations()
{
	//to do

}

std::string GameObject::GetName()
{
	return name;
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
	if (Transform* t = dynamic_cast<Transform*>(_c))
	{
		DeleteTransform(t);
	}
	else if (Light* l = dynamic_cast<Light*>(_c))
	{
		DeleteLight(l);
	}
	else // Add more conditions and function when new component created
	{
	}
}

void GameObject::DeleteAllComponents()
{
	for (Component* c : m_components)
	{
		RemoveComponent(c);
	}
}

