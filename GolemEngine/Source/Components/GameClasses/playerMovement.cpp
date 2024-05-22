#include "Components/GameClasses/playerMovement.h"
#include "Inputs/inputManager.h"

#include <iostream>

#include "Core/gameobject.h"

PlayerMovement::PlayerMovement()
{
}

PlayerMovement::~PlayerMovement()
{
}


void PlayerMovement::Begin()
{
	m_capsuleCollider = owner->GetComponent<CapsuleCollider>();
	m_capsuleCollider->motionType = MotionType::Dynamic;
	m_capsuleCollider->isActivated = true;
	m_capsuleCollider->onCollisionEnter = [this](Collider* _collider, Collider* _other) -> void { OnCollisionEnter(m_capsuleCollider, _other); };
}

void PlayerMovement::Update()
{
	MoveArround();
}

void PlayerMovement::MoveArround()
{
	if (InputManager::IsKeyPressed(KEY_W))
		PhysicSystem::AddVelocity(m_capsuleCollider->id, Vector3(0.f, 0.f, -0.1f));
	if (InputManager::IsKeyPressed(KEY_S))
		PhysicSystem::AddVelocity(m_capsuleCollider->id, Vector3(0.f, 0.f, 0.1f));
	if (InputManager::IsKeyPressed(KEY_A))
		PhysicSystem::AddVelocity(m_capsuleCollider->id, Vector3(-0.1f, 0.f, 0.f));
	if (InputManager::IsKeyPressed(KEY_D))
		PhysicSystem::AddVelocity(m_capsuleCollider->id, Vector3(0.1f, 0.f, 0.f));
}


void PlayerMovement::OnCollisionEnter(Collider* _collider, Collider* _other)
{
	PhysicSystem::AddForce(_collider->id, Vector3(0, 1, 0), bounceForce);
}
