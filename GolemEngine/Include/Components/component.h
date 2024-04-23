#pragma once

#include <nlohmann/json.hpp>

#include "Refl/refl.hpp"
#include "Reflection/attributes.h"

using json = nlohmann::json;


class GameObject;

class Component
{
public:
	GameObject* owner;

public:
	virtual ~Component();

	virtual void Begin() {};

	virtual void Update() {};

	
	virtual void to_json(json& j) const = 0;    // Virtual function to serialize component to JSON
}; 

REFL_AUTO(
	type(Component)
)