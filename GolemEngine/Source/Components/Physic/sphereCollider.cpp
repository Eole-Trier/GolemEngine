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
	BodyInterface& body_interface = PhysicSystem::physicsSystem.GetBodyInterface();
	// Remove the sphere from the physics system. Note that the sphere itself keeps all of its state and can be re-added at any time.
	body_interface.RemoveBody(id);

	// Destroy the sphere. After this the sphere ID is no longer valid.
	body_interface.DestroyBody(id);
}

void SphereCollider::Begin()
{
	BodyInterface& body_interface = PhysicSystem::physicsSystem.GetBodyInterface();

	id = PhysicSystem::CreateSphereCollider(owner->transform->localPosition, m_radius);
	
	body_interface.SetLinearVelocity(id, Vec3(0.0f, 5.0f, -25.0f));
}


void SphereCollider::Update()
{
	BodyInterface& body_interface = PhysicSystem::physicsSystem.GetBodyInterface();
	if (body_interface.IsActive(id))
	{
		RVec3 position = body_interface.GetCenterOfMassPosition(id);
		owner->transform->localPosition = Vector3(position.GetX(), position.GetY(), position.GetZ());
	}
}
