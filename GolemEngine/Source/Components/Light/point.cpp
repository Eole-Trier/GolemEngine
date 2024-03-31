#include "Components/Light/Point.h"

#include "Debug/log.h"
#include "Resource/Rendering/shader.h"
#include "Core/gameObject.h"
#include "matrix4.h"

PointLight::PointLight(const Vector4& _diffuse, const Vector4& _ambient, const Vector4& _specular, const Vector3& _position, 
    const float _constant, const float _linear, const float _quadratic, std::vector<PointLight*> _pointLights, size_t _maxPoints)
    : Light(_diffuse, _ambient, _specular), position(_position), constant(_constant), linear(_linear), quadratic(_quadratic)
{
    id = _pointLights.size();
    if (id >= _maxPoints)
    {
        Log::Print("The Point light %d will not be used. Point lights limit : %d", id, _maxPoints);
    }

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
        position = owner->transform->GetGlobalModel().TrsToPosition();
    SetPointLight(_shader);
}
