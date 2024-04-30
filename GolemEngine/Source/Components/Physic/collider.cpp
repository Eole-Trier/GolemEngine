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
	switch (m_MotionType)
	{
	case MotionType::Static:
		PhysicSystem::MakeBodyStatic(id);
		break;
	case MotionType::Kinematic:
		break;
	case MotionType::Dynamic:
		PhysicSystem::MakeBodyDynamic(id);
		break;
	default:
		break;
	}
	if (m_IsActivated)
	{
		PhysicSystem::ActivateBody(id);
	}
	else
	{
		PhysicSystem::DesactivateBody(id);
	}
}