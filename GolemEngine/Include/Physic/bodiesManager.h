#pragma once

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/BodyManager.h>

class BodiesManager
{
public:
	JPH::BodyManager* bodyManager = nullptr;

public:
	BodiesManager();
	~BodiesManager();
};