#pragma once

#include <string>
#include <vector>
#include "dll.h"

class Transform;
class Component;

class GameObject
{
private:
	std::string m_name;
	std::vector<Component*> m_components;

	bool selected;

public:
	Transform* transform;

public:
	GameObject(const std::string& _name, Transform* _transform);
	~GameObject();

	void AddComponent(Component* _component);

	void Selected();
	void Deselected();

	void Update();

	void DisplayInformations();

	GOLEM_ENGINE_API std::string GetName();

	/*GameObject* Instantiate();
	void Destroy();*/
};