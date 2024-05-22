#pragma once
#include "dll.h"
#include "Refl/refl.hpp"
#include "Components/component.h"
#include "Core/gameobject.h"
#include "Inputs/inputManager.h"
#include "Components/GameClasses/bullet.h"
#include <vector>

#include "Components/script.h"

class GOLEM_ENGINE_API Shot : public Script
{
private:

public:
	Shot();
	~Shot();

	float radius;

	float interval = 1.5f;
	float currentInteval;
	float bulletLifetime = 2.0f;


	void Begin() override;
	void Update() override;

	void instantiateBullet();

	void ToJson(json& j) const {}
};

REFL_AUTO(
	type(Shot, bases<Script>),
	field(radius),
	field(interval),
	field(bulletLifetime)
)