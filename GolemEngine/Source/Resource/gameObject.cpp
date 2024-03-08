#include "..\..\Include\Resource\gameObject.h"

GameObject::~GameObject()
{
}

void GameObject::AddComponent(Component* _component)
{
	m_components.push_back(_component);
	_component->SetOwner(this);
}

void GameObject::Update()
{
	for (auto& component : m_components)
	{
		component->Update();
	}
}

void GameObject::DisplayInformations()
{
	//to do
}

/*GameObject* GameObject::Instantiate()
{
	return nullptr;
}

void GameObject::Destroy()
{

}*/


void Component::SetOwner(GameObject* _owner)
{
	owner = _owner;
}

void Transform::Update()
{
}

void Light::Update()
{
}
