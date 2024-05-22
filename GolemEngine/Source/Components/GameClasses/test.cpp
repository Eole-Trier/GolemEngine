#include "Components/GameClasses/test.h"

#include <iostream>

#include "Core/gameobject.h"

Test::Test()
{
	std::cout << "Test Script Created" << std::endl;
}

Test::~Test()
{
	std::cout << "Test Script Deleted" << std::endl;
}


void Test::Begin()
{
	// some examples
	std::cout << "Test Script Begin owned by " << owner->name << std::endl;
	m_sphereCollider = owner->GetComponent<SphereCollider>();
	m_sphereCollider->radius = 2.0f;
	m_sphereCollider->motionType = MotionType::Dynamic;
	m_sphereCollider->isActivated = true;
	m_sphereCollider->onCollisionEnter = [this](Collider* _collider, Collider* _other) -> void { FunctionThatIGiveToACollider(m_sphereCollider, _other); };
}

void Test::Update()
{
	std::cout << "Test Script Update owned by " << owner->name << std::endl;
}

void Test::FunctionThatIGiveToACollider(Collider* _collider, Collider* _other)
{
	// Do what you want
	PhysicSystem::SetVelocity(_collider->id, Vector3(1, 5, 1));
}
