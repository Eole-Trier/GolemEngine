#include <vector>

#include "Debug/log.h"
#include "Resource/Rendering/shader.h"
#include "Components/Light/Point.h"

PointLight::PointLight(const Vector4& diffuse, const Vector4& ambient, const Vector4& specular, const Vector3& position, 
    const float constant, const float linear, const float quadratic, std::vector<PointLight*> _pointLights, size_t _maxPoints)
{
    diffuseColor = diffuse;
    ambientColor = ambient;
    specularColor = specular;
    this->position = position;
    this->constant = constant;
    this->linear = linear;
    this->quadratic = quadratic;
    id = _pointLights.size();
    if (id >= _maxPoints)
    {
        Log::Print("The Point light %d will not be used. Point lights limit : %d", id, _maxPoints);
    }

}

void PointLight::SetPointLight(Shader* shader)
{
    shader->SetVec3("pointLights[" + std::to_string(id) + "].position", position);
    shader->SetVec4("pointLights[" + std::to_string(id) + "].ambient", ambientColor);
    shader->SetVec4("pointLights[" + std::to_string(id) + "].diffuse", diffuseColor);
    shader->SetVec4("pointLights[" + std::to_string(id) + "].specular", specularColor);
    shader->SetFloat("pointLights[" + std::to_string(id) + "].constant", constant);
    shader->SetFloat("pointLights[" + std::to_string(id) + "].linear", linear);
    shader->SetFloat("pointLights[" + std::to_string(id) + "].quadratic", quadratic);
}