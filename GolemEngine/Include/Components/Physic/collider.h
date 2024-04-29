#pragma once

#include "Components/component.h"

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>

#include "Components/component.h"
#include "Refl/refl.hpp"

using namespace JPH;

class Collider : public Component
{
public:
	BodyID id;

public:
	Collider();
	~Collider();

	void Begin() override;

	void Update() override;

	void ToJson(json& j) const {}
};

REFL_AUTO(
	type(Collider, bases<Component>)
	
)