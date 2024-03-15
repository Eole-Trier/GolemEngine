#pragma once

class GameObject;

class Component
{
public:
	GameObject* owner;

public:
	virtual void Update() = 0;
};