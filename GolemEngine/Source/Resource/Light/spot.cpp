
#include <MathsLib/utils.h>
#include "Resource/Rendering/shader.h"
#include "Resource/Light/Spot.h"
#include "vector4.h"


SpotLight::SpotLight(const Vector4& diffuse, const Vector4& ambient, const Vector4& specular, const Vector3& position, const Vector3& direction, const float constant, const float linear,
    const float quadratic, const float cutOff, const float outerCutOff, int id)
{
    diffuseColor = diffuse;
    ambientColor = ambient;
    specularColor = specular;
    this->position = position;
    this->direction = direction;
    this->constant = constant;
    this->linear = linear;
    this->quadratic = quadratic;
    this->cutOff = cutOff;
    this->outerCutOff = outerCutOff;
    this->id = id;

};
void SpotLight::SetSpotLight(Shader* shader)
{
    shader->SetVec3("spotLights[" + std::to_string(id) + "].position", position);
    shader->SetVec3("spotLights[" + std::to_string(id) + "].direction", direction);
    shader->SetVec4("spotLights[" + std::to_string(id) + "].ambient", ambientColor);
    shader->SetVec4("spotLights[" + std::to_string(id) + "].diffuse", diffuseColor);
    shader->SetVec4("spotLights[" + std::to_string(id) + "].specular", specularColor);
    shader->SetFloat("spotLights[" + std::to_string(id) + "].constant", constant);
    shader->SetFloat("spotLights[" + std::to_string(id) + "].linear", linear);
    shader->SetFloat("spotLights[" + std::to_string(id) + "].quadratic", quadratic);
    shader->SetFloat("spotLights[" + std::to_string(id) + "].cutOff", cos(DegToRad(cutOff)));
    shader->SetFloat("spotLights[" + std::to_string(id) + "].outerCutOff", cos(DegToRad(outerCutOff)));
}