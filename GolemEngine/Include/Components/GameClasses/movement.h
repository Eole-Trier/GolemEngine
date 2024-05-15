#pragma once
#include "dll.h"
#include "Refl/refl.hpp"
#include "Components/component.h"
#include "vector3.h"

class GOLEM_ENGINE_API Movement : public Component
{
private:
	friend refl_impl::metadata::type_info__<Movement>;
public:
	Movement();
	~Movement();
	void Update() override;

    float moveSpeed = 1.0f;
    float rotateSpeed = 5;

    Vector3 front;
    Vector3 up;
    Vector3 right;
    Vector3 worldUp;

    bool moveMode = false;

    void ToJson(json& j) const
    {
        j = json
        {
            
        };
    }
};

REFL_AUTO(
    type(Movement),
    field(moveSpeed),
    field(moveMode)
)