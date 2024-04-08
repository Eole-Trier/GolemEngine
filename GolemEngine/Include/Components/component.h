#pragma once

#include "Refl/refl.hpp"
#include "Reflection/attributes.h"

class GameObject;

class Component
{
public:
	GameObject* owner;

public:
	virtual ~Component();

	virtual void Update() {};
}; 

REFL_AUTO(
	type(Component)
)