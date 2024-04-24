#pragma once

#include <Jolt/Jolt.h>
#include <Jolt/Physics/PhysicsSystem.h>

#include "Physic/bodyActivationManager.h"
#include "Physic/contactManager.h"
#include "Physic/objectLayerVsBroadPhaseLayer.h"
#include "Physic/objectLayerVsObjectLayer.h"
#include "Physic/broadPhaseLayerInterface.h"
#include "MathsLib/vector3.h"

#include "dll.h"

using namespace JPH;

class PhysicSystem
{
private:
	static RVec3 ToJph(Vector3 _v);
	static Quat ToJph(Quaternion _q);

public:
	// We simulate the physics world in discrete time steps. 60 Hz is a good rate to update the physics system.
	static constexpr float cDeltaTime = 1.0f / 60.0f;
	static constexpr int cCollisionSteps = 1;

	GOLEM_ENGINE_API static inline PhysicsSystem physicsSystem;
	GOLEM_ENGINE_API static inline BodyActivationManager bodyActivationListener;
	GOLEM_ENGINE_API static inline ContactManager contactListener;

	GOLEM_ENGINE_API static inline BPLInterface broadPhaseLayerInterface;
	GOLEM_ENGINE_API static inline ObjectLayerVsBroadPhaseLayer objectVsBroadphaseLayerFilter;
	GOLEM_ENGINE_API static inline ObjectLayerVsObjectLayer objectVsObjectLayerFilter;

	static Vector3 ToVector3(RVec3 _v);
	static Quaternion ToQuaternion(Quat _q);

public:
	PhysicSystem();
	~PhysicSystem();

	static void Update();
	static BodyID CreateSphereCollider(Vector3 _position, float _radius);
	static BodyID CreateBoxCollider(Vector3 _position, Vector3 _size);

};