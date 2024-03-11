#pragma once

#include <string>
#include <vector>

class Component;

class GameObject
{
private:
	std::string m_name;
	std::vector<Component*> m_components;

	bool selected;

public:
	GameObject(const std::string& _name);
	~GameObject();

	void AddComponent(Component* _component);

	void Selected();
	void Deselected();

	void Update();

	void DisplayInformations();

	/*GameObject* Instantiate();
	void Destroy();*/
};