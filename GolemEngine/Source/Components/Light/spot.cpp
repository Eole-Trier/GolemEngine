#include "Components/Light/Spot.h"

#include <MathsLib/utils.h>

#include "Debug/log.h"
#include "Resource/Rendering/shader.h"
#include "Core/gameObject.h"
#include "Resource/sceneManager.h"

SpotLight::SpotLight()
{
    std::vector<SpotLight*> spotLights = SceneManager::GetCurrentScene()->GetSpotLights();
    size_t maxSpots = SceneManager::GetCurrentScene()->GetMaxSpotLights();

    diffuseColor = Vector4(1.f, 1.f, 1.f, 1.f);
    ambientColor = Vector4(1.f, 1.f, 1.f, 1.f);
    specularColor = Vector4(1.f, 1.f, 1.f, 1.f);
    direction = Vector3(1.f, 0.f, 0.f);
    constant = 1.f;
    linear = 0.f;
    quadratic = 0.f;
    cutOff = 1.f;
    outerCutOff = 3.f;

    id = spotLights.size();
    if (id >= maxSpots)
    {
        Log::Print("The SpotLight %d will not be used. SpotLights limit : %d", id, maxSpots);
    }
    else
    {
        SceneManager::GetCurrentScene()->AddLight(this);
    }
}

SpotLight::SpotLight(const Vector4& _diffuse, const Vector4& _ambient, const Vector4& _specular, const Vector3& _position, const Vector3& _direction, const float _constant, 
    const float _linear, const float _quadratic, const float _cutOff, const float _outerCutOff)
    : Light(_diffuse, _ambient, _specular), position(_position), direction(_direction), constant(_constant), linear(_linear), quadratic(_quadratic), 
    cutOff(_cutOff), outerCutOff(_outerCutOff)
{
    std::vector<SpotLight*> spotLights = SceneManager::GetCurrentScene()->GetSpotLights();
    size_t maxSpots = SceneManager::GetCurrentScene()->GetMaxSpotLights();

    id = spotLights.size();
    if (id >= maxSpots)
    {
        Log::Print("The SpotLight %d will not be used. SpotLights limit : %d", id, maxSpots);
    }
    else
    {
        SceneManager::GetCurrentScene()->AddLight(this);
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
