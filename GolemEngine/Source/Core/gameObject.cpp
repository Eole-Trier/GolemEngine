#include "Core/gameObject.h"
#include "Core/transform.h"
#include "Components/component.h"

GameObject::GameObject(const std::string& _name, Transform* _transform) 
	: name(_name), transform(_transform), m_selected(false)
{
	AddComponent(_transform);
}

GameObject::~GameObject() {}

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

