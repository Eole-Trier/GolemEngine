#pragma once

#include "dll.h"

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/Body.h>
#include <Jolt/Physics/Body/BodyManager.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Collision/ObjectLayer.h>
#include "Components/component.h"


class RigidBody : public Component
{
private:
	JPH::Body* m_body = nullptr;
	JPH::BodyCreationSettings* m_bodyCreationSettings = nullptr;
	JPH::BodyManager* m_bodyManager = nullptr;
	
public:
	RigidBody();
	~RigidBody();



	void to_json(json& j) const {}
};