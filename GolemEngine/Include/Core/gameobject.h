#pragma once

#include <string>
#include <vector>
#include <type_traits>
#include <nlohmann/json.hpp>

#include "dll.h"
#include "Refl/refl.hpp"
#include "Components/transform.h"
#include "Resource/guid.h"
#include "Debug/log.h"
#include "Components/Light/light.h"

using json = nlohmann::json;


class GOLEM_ENGINE_API GameObject
{
private:
	size_t m_id;
	std::vector<Component*> m_components;
	bool m_selected;

public:
	Guid guid;
	std::string name;
	Transform* transform = nullptr;

public:
	GameObject();
	GameObject(const std::string& _name, Transform* _transform);
	virtual ~GameObject();

	void Update();

	size_t GetId();
	void SetId(size_t _id);

	void DeleteTransform(Transform* _t);
	void DeleteLight(Light* _l);

	void RemoveComponent(Component* _c);
	void DeleteAllComponents();

	template<typename TypeT>
	void AddComponent(TypeT* _type);
	template<typename TypeT>
	void AddComponent();

	template<typename TypeT>
	TypeT* GetComponent(); 

	template<typename TypeT>
	std::vector<TypeT*> GetComponents();

	friend refl_impl::metadata::type_info__<GameObject>; // needed to reflect private members

	// Define serialization and deserialization functions manually because the
	// macro is not used due to the pointer member variable.
	void ToJson(json& j) const
	{
		j = json
		{
			{"name", name},
			{"guid", guid.ToString()}
		};
		if (!m_components.empty())
		{
			json jComponents;
			for (int i = 0; i < m_components.size(); i++)
			{
				json jComponentPtr;
				m_components[i]->ToJson(jComponentPtr);
				jComponents.push_back(jComponentPtr);
			}
			
			j["components"] = jComponents;
		}
	}

};

template<typename TypeT>
void GameObject::AddComponent(TypeT* _type)
{
	if (GetComponent<TypeT>())
	{
		Log::Print("The GameObject already has a Component of type TypeT");
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
		if (t)
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
		if (t)
		{
			components.push_back(t);
		}
	}
	return components;
}

REFL_AUTO(
	type(GameObject),
	field(name),
	field(m_components)
)