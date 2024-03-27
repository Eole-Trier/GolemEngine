#pragma once

#include <vector>

#include <vector3.h>

#include "dll.h"
#include "Components/Light/Light.h"
#include "Reflection/refl.hpp"

class Shader;

class GOLEM_ENGINE_API SpotLight : public Light
{
public:
    size_t id;
    Vector3 position;
    Vector3 direction;
    float constant;
    float linear;
    float quadratic;
    float cutOff;
    float outerCutOff;

public:
    SpotLight() = default;
    SpotLight(const Vector4& _diffuse, const Vector4& _ambient, const Vector4& _specular, const Vector3& _position, const Vector3& _direction, const float _constant, const float _linear,
        const float _quadratic, const float _cutOff, const float _outerCutOff, std::vector<SpotLight*> _spotLights, size_t _maxSpots);
    void SetSpotLight(Shader* _shader);

    void Update(Shader* _shader) override;
};

REFL_AUTO(
    type(SpotLight, bases<Light>),
    field(direction),
    field(constant),
    field(linear),
    field(quadratic),
    field(cutOff),
    field(outerCutOff)
)