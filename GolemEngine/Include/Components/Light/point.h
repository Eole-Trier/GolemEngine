#pragma once

#include <vector>

#include <vector3.h>

#include "dll.h"
#include "Components/Light/Light.h"
#include "Reflection/refl.hpp"

class Shader;

class GOLEM_ENGINE_API PointLight : public Light
{
public:
    size_t id;
    Vector3 position;
    float constant;
    float linear;
    float quadratic;

public:
    PointLight() = default;
    PointLight(const Vector4& _diffuse, const Vector4& _ambient, const Vector4& _specular, const Vector3& _position, 
        const float _constant, const float _linear, const float _quadratic, std::vector<PointLight*> _pointLights, size_t _maxPoints);
    void SetPointLight(Shader* _shader);
   
    void Update(Shader* _shader) override;
};

REFL_AUTO(
    type(PointLight, bases<Light>),
    field(constant),
    field(linear),
    field(quadratic)
)