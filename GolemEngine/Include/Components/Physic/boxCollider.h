#pragma once

#include "dll.h"

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include "Components/Physic/collider.h"
#include "Core/gameobject.h"
#include "Refl/refl.hpp"

using namespace JPH;

class BoxCollider : public Collider
{
private:
	Vector3 m_size;

public:
	BodyID id;

public:
	BoxCollider();
	BoxCollider(Vector3 _size);
	~BoxCollider();

	void Begin() override;

	void Update() override;

	friend refl_impl::metadata::type_info__<BoxCollider>; // needed to reflect private members
};

REFL_AUTO(
	type(BoxCollider, bases<Component>),
	field(m_size)
)