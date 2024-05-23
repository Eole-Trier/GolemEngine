#pragma once

#include "Components/script.h"
#include "Components/Physic/capsuleCollider.h"
#include "Core/gameobject.h"
#include "Resource/resourceManager.h"
#include "Refl/refl.hpp"

class Spawner : public Script
{
private:

public:

	Spawner();
	~Spawner();

	void Begin() override;
	void Update() override;

	int spawnRange;
	int spawnCount = 10;
	float interval;
	float spawnInterval = 1.0f;

	void Spawn(const std::string& _name);

	void ToJson(json& j) const {}
};

REFL_AUTO(
	type(Spawner, bases<Script>),
	field(spawnCount),
	field(spawnRange),
	field(spawnInterval)
)