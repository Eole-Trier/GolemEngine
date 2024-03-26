#pragma once

#include "Reflection/refl.hpp"

class GameObject;

class Component
{
public:
	GameObject* owner;

public:
	virtual void Update() = 0;
}; 

REFL_AUTO(
	type(Component)
)