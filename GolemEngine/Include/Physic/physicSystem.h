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



enum class MotionType : uint8
{
	Static,						
	Kinematic,					
	Dynamic,
};

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


public:
	PhysicSystem();
	~PhysicSystem();

	static Vector3 ToVector3(RVec3 _v);
	static Quaternion ToQuaternion(Quat _q);

	static void Update();

	static BodyID CreateSphereCollider(Vector3 _position, Quaternion _rotation, float _radius, EMotionType _motionType = EMotionType::Static, ObjectLayer _objectLayer = ObjectLayers::NON_MOVING);
	static BodyID CreateBoxCollider(Vector3 _position, Quaternion _rotation, Vector3 _size, EMotionType _motionType = EMotionType::Static, ObjectLayer _objectLayer = ObjectLayers::NON_MOVING);


	static void MakeBodyStatic(BodyID _bodyId);
	static void MakeBodyDynamic(BodyID _bodyId);
	static void MakeBodyKinematic(BodyID _bodyId);

	static void ActivateBody(BodyID _bodyId);
	static void DeactivateBody(BodyID _bodyId, Vector3 _position);

	static void AddForce(BodyID _bodyId, Vector3 _force);

	static void SetSphereShape(BodyID _bodyId, float _radius);
	static void SetBoxShape(BodyID _bodyId, Vector3 _size);
};