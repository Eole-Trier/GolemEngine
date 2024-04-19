#include "Components/Physic/sphereCollider.h"

#include <Jolt/Physics/Body/BodyInterface.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>

#include <iostream>

#include "Physic/physicSystem.h"
#include "Physic/layers.h"

using namespace JPH;
using namespace JPH::literals;

SphereCollider::SphereCollider(GameObject* _owner, float _radius)
	: m_radius(_radius)
{
	owner = _owner;
	BodyInterface& body_interface = PhysicSystem::physicsSystem.GetBodyInterface();

	BodyCreationSettings sphere_settings(new SphereShape(_radius), RVec3(owner->transform->localPosition.x, owner->transform->localPosition.y, owner->transform->localPosition.z), Quat::sIdentity(), EMotionType::Dynamic, ObjectLayers::MOVING);
	id = body_interface.CreateAndAddBody(sphere_settings, EActivation::Activate);

	// Now you can interact with the dynamic body, in this case we're going to give it a velocity.
	// (note that if we had used CreateBody then we could have set the velocity straight on the body before adding it to the physics system)
	body_interface.SetLinearVelocity(id, Vec3(0.0f, -5.0f, 0.0f));
}


SphereCollider::~SphereCollider()
{
	BodyInterface& body_interface = PhysicSystem::physicsSystem.GetBodyInterface();
	// Remove the sphere from the physics system. Note that the sphere itself keeps all of its state and can be re-added at any time.
	body_interface.RemoveBody(id);

	// Destroy the sphere. After this the sphere ID is no longer valid.
	body_interface.DestroyBody(id);
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
