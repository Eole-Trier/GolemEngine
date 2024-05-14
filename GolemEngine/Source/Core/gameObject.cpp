#include "Core/gameObject.h"
#include "Components/component.h"
#include "golemEngine.h"
#include "Resource/sceneManager.h"
#include "golemEngine.h"
#include "Reflection/classesManager.h"

GameObject::GameObject()
	: IsSelected(false)
{
	name = "New GameObject";
	m_id = SceneManager::GetCurrentScene()->gameObjects.size();
	AddComponent(new Transform);
	transform = GetComponent<Transform>();
	SceneManager::GetCurrentScene()->gameObjects.push_back(this);
}

GameObject::GameObject(const std::string& _name, Transform* _transform) 
	: name(_name), IsSelected(false)
{
	m_id = SceneManager::GetCurrentScene()->gameObjects.size();
	AddComponent(_transform);
	transform = GetComponent<Transform>();
	SceneManager::GetCurrentScene()->gameObjects.push_back(this);
}

GameObject::~GameObject() 
{
	SceneManager::GetCurrentScene()->RemoveGameObject(this);
	DeleteAllComponents();
}

void GameObject::Update()
{
	for (Component* c : m_components)
	{
		c->Update();
	}
}

bool GameObject::HasComponent(const std::string& _name) const
{
	size_t hash = ClassesManager::GetHashCodeFromName(_name);

	for (Component* c : m_components)
	{
		size_t otherHash = typeid(*c).hash_code();

		if (hash == otherHash)
		{
			Log::Print("The GameObject already has a Component of this type");
			return true;
		}
	}

	return false;
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
	std::erase(m_components, _c);
	delete _c;
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

void GameObject::AddComponent(Component* _type)
{	
	m_components.push_back(_type);
	_type->owner = this;
	return;
}
