#pragma once

#include <Jolt/Jolt.h>
#include <Jolt/Physics/PhysicsSystem.h>

using namespace JPH;

class PhysicSystem
{
private:

public:
	// We simulate the physics world in discrete time steps. 60 Hz is a good rate to update the physics system.
	static inline const float cDeltaTime = 1.0f / 60.0f;
	static inline int cCollisionSteps = 1;
	static PhysicsSystem physicsSystem;

public:
	PhysicSystem();
	~PhysicSystem();

	static void Update();
};