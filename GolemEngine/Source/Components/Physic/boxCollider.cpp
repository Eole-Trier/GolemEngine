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
	BodyInterface& bodyInterface = PhysicSystem::physicsSystem.GetBodyInterface();

	id = PhysicSystem::CreateBoxCollider(owner->transform->localPosition, Quaternion::EulerToQuaternion(owner->transform->rotation), m_size);
}

void BoxCollider::Update()
{
	Collider::Update();
	BodyInterface& bodyInterface = PhysicSystem::physicsSystem.GetBodyInterface();
	PhysicSystem::SetBoxShape(id, m_size);
}