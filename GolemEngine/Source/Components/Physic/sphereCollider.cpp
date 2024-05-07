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
	BodyInterface& bodyInterface = PhysicSystem::physicsSystem.GetBodyInterface();
	id = PhysicSystem::CreateSphereCollider(owner->transform->localPosition, Quaternion::EulerToQuaternion(owner->transform->rotation), m_radius);
}

void SphereCollider::Update()
{
	Collider::Update();
	BodyInterface& bodyInterface = PhysicSystem::physicsSystem.GetBodyInterface();
	PhysicSystem::SetSphereShape(id, m_radius);
}
