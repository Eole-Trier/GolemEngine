#pragma once
#include "vector3.h"
#include <string>
#include <vector>

class Component;

class GameObject
{
private:
	std::string m_name;
	std::vector<Component*> m_components;

public:
	GameObject(const std::string& _name) : m_name(_name) {}
	~GameObject();

	void AddComponent(Component* _component);

	void Update();

	void DisplayInformations();

	/*GameObject* Instantiate();
	void Destroy();*/
};


class Component 
{
public:
	virtual void Update() = 0;
	void SetOwner(GameObject* _owner);

protected:
	GameObject* owner;
};


class Transform : public Component
{
public:
	void Update() override;

private:
	Vector3 m_transform;
	Vector3 m_rotation;
	Vector3 m_scaling;
};

/*class Light : public Component
{
public:
	void Update() override;

private:
	float m_intensity;
	Vector3 m_position;
	Vector3 m_color;
};*/
