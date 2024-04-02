#include "Components/Light/Spot.h"

#include <MathsLib/utils.h>

#include "Debug/log.h"
#include "Resource/Rendering/shader.h"
#include "Core/gameObject.h"
#include "Resource/sceneManager.h"

SpotLight::SpotLight(const Vector4& _diffuse, const Vector4& _ambient, const Vector4& _specular, const Vector3& _position, const Vector3& _direction, const float _constant, 
    const float _linear, const float _quadratic, const float _cutOff, const float _outerCutOff, std::vector<SpotLight*> _spotLights, size_t _maxSpots)
    : Light(_diffuse, _ambient, _specular), position(_position), direction(_direction), constant(_constant), linear(_linear), quadratic(_quadratic), 
    cutOff(_cutOff), outerCutOff(_outerCutOff)
{
    id = _spotLights.size();
    if (id >= _maxSpots)
    {
        Log::Print("The Spot light %d will not be used. Spot lights limit : %d", id, _maxSpots);
    }
};

SpotLight::~SpotLight()
{
    SceneManager::GetCurrentScene()->DeleteLight(this);
}

void SpotLight::SetSpotLight(Shader* _shader)
{
    _shader->SetVec3("spotLights[" + std::to_string(id) + "].position", position);
    _shader->SetVec3("spotLights[" + std::to_string(id) + "].direction", direction);
    _shader->SetVec4("spotLights[" + std::to_string(id) + "].ambient", ambientColor);
    _shader->SetVec4("spotLights[" + std::to_string(id) + "].diffuse", diffuseColor);
    _shader->SetVec4("spotLights[" + std::to_string(id) + "].specular", specularColor);
    _shader->SetFloat("spotLights[" + std::to_string(id) + "].constant", constant);
    _shader->SetFloat("spotLights[" + std::to_string(id) + "].linear", linear);
    _shader->SetFloat("spotLights[" + std::to_string(id) + "].quadratic", quadratic);
    _shader->SetFloat("spotLights[" + std::to_string(id) + "].cutOff", cos(DegToRad(cutOff)));
    _shader->SetFloat("spotLights[" + std::to_string(id) + "].outerCutOff", cos(DegToRad(outerCutOff)));
}

void SpotLight::Update(Shader* _shader)
{
    if (owner)
        position = owner->transform->globalPosition;
    SetSpotLight(_shader);
}
