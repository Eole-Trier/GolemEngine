#include "Core/gameobject.h"
#include "Core/transform.h"
#include "Components/component.h"

GameObject::GameObject(const std::string& _name, Transform* _transform) :
	name(_name), transform(_transform)
{
	selected = false;
	_transform->owner = this;
}

GameObject::~GameObject()
{
}

void GameObject::AddComponent(Component* _component)
{
	m_components.push_back(_component);
	_component->owner = this;
}

void GameObject::Selected()
{
	selected = true;
}

void GameObject::Deselected()
{
	selected = false;
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

std::string GameObject::GetName()
{
	return name;
}

/*GameObject* GameObject::Instantiate()
{
	return nullptr;
}

void GameObject::Destroy()
{

}*/