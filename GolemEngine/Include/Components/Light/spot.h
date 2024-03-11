#pragma once

#include "dll.h"
#include "Components/Light/Light.h"

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

    SpotLight(const Vector4& diffuse, const Vector4& ambient, const Vector4& specular, const Vector3& position, const Vector3& direction, const float constant, const float linear,
        const float quadratic, const float cutOff, const float outerCutOff, std::vector<SpotLight*> _spotLights, size_t _maxSpots);
    void SetSpotLight(Shader* shader);
};