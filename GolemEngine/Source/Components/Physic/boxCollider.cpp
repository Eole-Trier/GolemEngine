#include "Components/Physic/boxCollider.h"

#include <Jolt/Physics/Body/BodyInterface.h>

#include <iostream>

#include "Physic/physicSystem.h"
#include "Physic/layers.h"

BoxCollider::BoxCollider()
	: m_size(Vector3(1.f, 1.f, 1.f))
{
}

BoxCollider::BoxCollider(Vector3 _size)
	: m_size(_size)
{
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::Begin()
{
	BodyInterface& body_interface = PhysicSystem::physicsSystem.GetBodyInterface();

	id = PhysicSystem::CreateBoxCollider(owner->transform->localPosition, m_size);
}

void BoxCollider::Update()
{
	BodyInterface& body_interface = PhysicSystem::physicsSystem.GetBodyInterface();
	if (body_interface.IsActive(id))
	{
		RVec3 position = body_interface.GetCenterOfMassPosition(id);
		owner->transform->localPosition = PhysicSystem::ToVector3(position);
	}
}