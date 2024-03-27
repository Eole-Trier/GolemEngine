#pragma once

#include <string>
#include <vector>
#include <type_traits>

#include "dll.h"
#include "Reflection/refl.hpp"
#include "Components/component.h"
#include "Debug/log.h"

class Transform;

class GOLEM_ENGINE_API GameObject
{
private:
	std::vector<Component*> m_components;
	bool m_selected;

public:
	std::string name;
	Transform* transform;

public:
	GameObject(const std::string& _name, Transform* _transform);
	~GameObject();


	void Update();
	void DisplayInformations();
	std::string GetName();

	template<typename TypeT>
	void AddComponent(TypeT* _type);
	template<typename TypeT>
	void AddComponent();

	template<typename TypeT>
	TypeT* GetComponent(); 

	template<typename TypeT>
	std::vector<TypeT*> GetComponents();
};

template<typename TypeT>
void GameObject::AddComponent(TypeT* _type)
{
	if (std::is_same_v<TypeT, Transform> && transform != nullptr)
	{
		Log::Print("The GameObject already have a Transform");
		return;
	}
	static_assert(std::is_base_of_v<Component, TypeT>, "TypeT isn't a component");
	m_components.push_back(_type);
	_type->owner = this;
}

template<typename TypeT>
void GameObject::AddComponent()
{
	static_assert(std::is_base_of_v<Component, TypeT>, "TypeT isn't a component");
	TypeT* t = new TypeT;
	m_components.push_back(t);
	t->owner = this;
}

template<typename TypeT>
TypeT* GameObject::GetComponent()
{
	for (Component* c : m_components)
	{
		auto t = dynamic_cast<TypeT*>(c);
		if (t != nullptr)
		{
			return t;
		}
	}
	return nullptr;
}

template<typename TypeT>
std::vector<TypeT*> GameObject::GetComponents()
{
	std::vector<TypeT*> components;
	for (Component* c : m_components)
	{
		auto t = dynamic_cast<TypeT*>(c);
		if (t != nullptr)
		{
			components.push_back(t);
		}
	}
	return components;
}

REFL_AUTO(
	type(GameObject),
	field(name),
	field(transform)
)
	//field(m_components)