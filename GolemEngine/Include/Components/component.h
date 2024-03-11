#pragma once

class GameObject;

class Component
{
public:
	virtual void Update() = 0;
	void SetOwner(GameObject* _owner);

protected:
	GameObject* owner;
};