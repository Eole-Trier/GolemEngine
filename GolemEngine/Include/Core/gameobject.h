#pragma once

#include <string>
#include <vector>

#include "dll.h"
#include "Reflection/refl.hpp"
#include "Components/component.h"

class Transform;

class GOLEM_ENGINE_API GameObject
{
private:
	std::vector<Component*> m_components;

	bool selected;

public:
	std::string name;
	Transform* transform;

public:
	GameObject(const std::string& _name, Transform* _transform);
	~GameObject();

	void AddComponent(Component* _component);

	void Update();

	void DisplayInformations();

	std::string GetName();

	/*GameObject* Instantiate();
	void Destroy();*/
};

REFL_AUTO(
	type(GameObject),
	field(name),
	field(transform)
	//field(m_components)
)