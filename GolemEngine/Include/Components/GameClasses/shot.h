#pragma once
#include "dll.h"
#include "Refl/refl.hpp"
#include "Components/component.h"
#include "Core/gameobject.h"
#include "Inputs/inputManager.h"
#include "Components/GameClasses/bullet.h"
#include <vector>


class GOLEM_ENGINE_API Shot : public Component
{
private:
public:
	Shot();
	~Shot();

	void Update() override;

    void instantiate();

	std::vector<Bullet*> bullets;

    float radius = 0.1f;

    void ToJson(json& j) const
    {
        j = json
        {

        };
    }
};

REFL_AUTO(
    type(Shot),
    field(radius)
)