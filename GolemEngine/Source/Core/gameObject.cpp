#include "Core/gameObject.h"
#include "Components/component.h"
#include "golemEngine.h"
#include "Resource/sceneManager.h"
#include "WorldBuilder/terrain.h"


GameObject::GameObject()
{
	name = "New GameObject";
	m_id = SceneManager::GetCurrentScene()->gameObjects.size();
	AddComponent(new Transform);
	transform = GetComponent<Transform>();
	SceneManager::GetCurrentScene()->gameObjects.push_back(this);
}

GameObject::GameObject(const std::string& _name, Transform* _transform) 
	: name(_name)
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

void GameObject::ToJson(json& _j) const
{
	_j = json
	{
		{"name", name},
		{"guid", guid.ToString()},
		{"isTerrain", m_isTerrain}
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
		
		_j["components"] = jComponents;
	}
	
	const Terrain* terrainPtr = dynamic_cast<const Terrain*>(this);
	if (terrainPtr)
	{
		json jTerrainData;
		terrainPtr->ToJson(jTerrainData);
		_j["terrainData"] = jTerrainData;
	}
}
