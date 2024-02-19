
#include "Resource/shader.h"
#include "Resource/Light/Point.h"

PointLight::PointLight(const Vector3& diffuse, const Vector3& ambient, const Vector3& specular, const Vector3& position, const float constant, const float linear, const float quadratic, int id)
{
    diffuseColor = diffuse;
    ambientColor = ambient;
    specularColor = specular;
    this->position = position;
    this->constant = constant;
    this->linear = linear;
    this->quadratic = quadratic;
    this->id = id;
}

void PointLight::SetPointLight(Shader* shader)
{
    shader->SetVec3("pointLights[" + std::to_string(id) + "].position", position);
    shader->SetVec3("pointLights[" + std::to_string(id) + "].ambient", ambientColor);
    shader->SetVec3("pointLights[" + std::to_string(id) + "].diffuse", diffuseColor);
    shader->SetVec3("pointLights[" + std::to_string(id) + "].specular", specularColor);
    shader->SetFloat("pointLights[" + std::to_string(id) + "].constant", constant);
    shader->SetFloat("pointLights[" + std::to_string(id) + "].linear", linear);
    shader->SetFloat("pointLights[" + std::to_string(id) + "].quadratic", quadratic);
}