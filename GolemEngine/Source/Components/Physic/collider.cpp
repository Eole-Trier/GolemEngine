#include "Components/Physic/collider.h"
#include "Physic/physicSystem.h"

Collider::Collider()
{

}

Collider::~Collider()
{
	BodyInterface& body_interface = PhysicSystem::physicsSystem.GetBodyInterface();
	// Remove the body from the physics system. Note that the body itself keeps all of its state and can be re-added at any time.
	body_interface.RemoveBody(id);

	// Destroy the body. After this the sphere ID is no longer valid.
	body_interface.DestroyBody(id);
}

void Collider::Begin()
{
}

void Collider::Update()
{

}