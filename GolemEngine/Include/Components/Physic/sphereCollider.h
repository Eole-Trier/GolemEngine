#pragma once

#include "dll.h"

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include "Components/component.h"
#include "Core/gameobject.h"

using namespace JPH;

class SphereCollider : public Component
{
private:
	float m_radius;

public:
	BodyID id;

public:
	SphereCollider(GameObject* _owner, float _radius);
	~SphereCollider();

	void Update() override;

	void to_json(json& j) const {}
};