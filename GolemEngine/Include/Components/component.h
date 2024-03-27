#pragma once

#include "Reflection/refl.hpp"
#include "Reflection/attributes.h"

class GameObject;

class Component
{
public:
	GameObject* owner;

public:
	virtual ~Component() = 0;

	virtual void Update() {};
}; 

REFL_AUTO(
	type(Component)
)