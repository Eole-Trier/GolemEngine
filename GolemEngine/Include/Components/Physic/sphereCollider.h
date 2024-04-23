#pragma once

#include "dll.h"

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include "Components/component.h"
#include "Core/gameobject.h"
#include "Refl/refl.hpp"

using namespace JPH;

class SphereCollider : public Component
{
private:
	float m_radius;

public:
	BodyID id;

public:
	SphereCollider();
	SphereCollider(float _radius);
	~SphereCollider();

	void Begin() override;

	void Update() override;

	void to_json(json& j) const {}

	friend refl_impl::metadata::type_info__<SphereCollider>; // needed to reflect private members
};

REFL_AUTO(
	type(SphereCollider, bases<Component>),
	field(m_radius, Range(0, 100))
)