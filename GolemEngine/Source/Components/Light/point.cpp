#include "Components/Light/Point.h"

#include "Debug/log.h"
#include "Resource/Rendering/shader.h"
#include "Core/gameObject.h"
#include "matrix4.h"
#include "Resource/sceneManager.h"

PointLight::PointLight()
{
    std::vector<PointLight*> pointLights = SceneManager::GetCurrentScene()->GetPointLights();
    size_t maxPoints = SceneManager::GetCurrentScene()->GetMaxPointLights();

    diffuseColor = Vector4(1.f, 1.f, 1.f, 1.f);
    ambientColor = Vector4(1.f, 1.f, 1.f, 1.f);
    specularColor = Vector4(1.f, 1.f, 1.f, 1.f);
    constant = 1.f;
    linear = 0.f;
    quadratic = 0.f;

    id = pointLights.size();
    if (id >= maxPoints)
    {
        Log::Print("The PointLight %d will not be used. PointLights limit : %d", id, maxPoints);
    }
    else
    {
        SceneManager::GetCurrentScene()->AddLight(this);
    }
}

PointLight::PointLight(const Vector4& _diffuse, const Vector4& _ambient, const Vector4& _specular, const Vector3& _position, 
    const float _constant, const float _linear, const float _quadratic)
    : Light(_diffuse, _ambient, _specular), position(_position), constant(_constant), linear(_linear), quadratic(_quadratic)
{
    std::vector<PointLight*> pointLights = SceneManager::GetCurrentScene()->GetPointLights();
    size_t maxPoints = SceneManager::GetCurrentScene()->GetMaxPointLights();

    id = pointLights.size();
    if (id >= maxPoints)
    {
        Log::Print("The PointLight %d will not be used. PointLights limit : %d", id, maxPoints);
    }
    else
    {
        SceneManager::GetCurrentScene()->AddLight(this);
    }
}

PointLight::~PointLight()
{
    SceneManager::GetCurrentScene()->DeleteLight(this);
}

void PointLight::SetPointLight(Shader* _shader)
{
    _shader->SetVec3("pointLights[" + std::to_string(id) + "].position", position);
    _shader->SetVec4("pointLights[" + std::to_string(id) + "].ambient", ambientColor);
    _shader->SetVec4("pointLights[" + std::to_string(id) + "].diffuse", diffuseColor);
    _shader->SetVec4("pointLights[" + std::to_string(id) + "].specular", specularColor);
    _shader->SetFloat("pointLights[" + std::to_string(id) + "].constant", constant);
    _shader->SetFloat("pointLights[" + std::to_string(id) + "].linear", linear);
    _shader->SetFloat("pointLights[" + std::to_string(id) + "].quadratic", quadratic);
}

void PointLight::Update(Shader* _shader)
{
    if (owner)
        position = owner->transform->globalPosition;
    SetPointLight(_shader);
}
