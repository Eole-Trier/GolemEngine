#pragma once

#include <vector>

#include <vector3.h>

#include "dll.h"
#include "Components/Light/Light.h"
#include "Refl/refl.hpp"
#include "Reflection/attributes.h"

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
    SpotLight();
    SpotLight(const Vector4& _diffuse, const Vector4& _ambient, const Vector4& _specular, const Vector3& _position, const Vector3& _direction, const float _constant, const float _linear,
        const float _quadratic, const float _cutOff, const float _outerCutOff);
    ~SpotLight();
    void SetSpotLight(Shader* _shader);

    void Update() override;


    // Define serialization and deserialization functions manually because the
    // macro is not used due to the pointer member variable.
    void ToJson(json& j) const override
    {
        j = json
        {
            {"name", "spotLight"},
            {"data",
                {
                   {"id", id},
                   {"diffuseColor", diffuseColor},
                   {"ambientColor", ambientColor},
                   {"specularColor", specularColor},
                   {"position", position},
                   {"direction", direction},
                   {"constant", constant},
                   {"linear", linear},
                   {"quadratic", quadratic},
                   {"cutOff", cutOff},
                   {"outerCutOff", outerCutOff},
                }
            }
        };
    }
};

REFL_AUTO(
    type(SpotLight, bases<Light>),
    field(direction),
    field(constant, Range(0, 1)),
    field(linear, Range(0, 1)),
    field(quadratic, Range(0, 1)),
    field(cutOff),
    field(outerCutOff)
)