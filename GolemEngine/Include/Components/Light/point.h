#pragma once

#include <vector>

#include <vector3.h>

#include "dll.h"
#include "Components/Light/Light.h"
#include "Refl/refl.hpp"
#include "Reflection/attributes.h"

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
    PointLight();
    PointLight(const Vector4& _diffuse, const Vector4& _ambient, const Vector4& _specular, const Vector3& _position, 
        const float _constant, const float _linear, const float _quadratic);
    ~PointLight();
    void SetPointLight(Shader* _shader);
   
    void Update(Shader* _shader) override;
};

REFL_AUTO(
    type(PointLight, bases<Light>),
    field(constant, Range(0, 1)),
    field(linear, Range(0, 1)),
    field(quadratic, Range(0, 1))
)