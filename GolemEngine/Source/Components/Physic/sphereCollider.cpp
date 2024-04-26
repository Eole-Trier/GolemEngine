#include "Components/Physic/sphereCollider.h"

#include <Jolt/Physics/Body/BodyInterface.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>

#include <iostream>

#include "Physic/physicSystem.h"
#include "Physic/layers.h"

using namespace JPH;
using namespace JPH::literals;

SphereCollider::SphereCollider()
	: m_radius(1.f)
{
}

SphereCollider::SphereCollider(float _radius)
	: m_radius(_radius)
{
}

SphereCollider::~SphereCollider()
{
}

void SphereCollider::Begin()
{
	BodyInterface& body_interface = PhysicSystem::physicsSystem.GetBodyInterface();

	id = PhysicSystem::CreateSphereCollider(owner->transform->localPosition, m_radius);
}

void SphereCollider::Update()
{
	BodyInterface& body_interface = PhysicSystem::physicsSystem.GetBodyInterface();
	if (body_interface.IsActive(id))
	{
		RVec3 position = body_interface.GetCenterOfMassPosition(id);
		owner->transform->localPosition = PhysicSystem::ToVector3(position);
	}
}
