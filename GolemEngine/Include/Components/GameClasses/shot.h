#pragma once
#include "dll.h"
#include "Refl/refl.hpp"
#include "Components/component.h"
#include "Core/gameobject.h"
#include "Inputs/inputManager.h"
#include "Components/GameClasses/bullet.h"
#include <vector>


class Shot : public Component
{
private:
public:
    GOLEM_ENGINE_API Shot();
    GOLEM_ENGINE_API ~Shot();

    GOLEM_ENGINE_API void Update() override;

    GOLEM_ENGINE_API void instantiate();

	std::vector<Bullet*> bullets;

    float radius = 0.1f;

    GOLEM_ENGINE_API void ToJson(json& j) const
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