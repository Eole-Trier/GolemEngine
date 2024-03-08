

#include "Resource/Rendering/shader.h"
#include "Components/Light/Directional.h"



DirectionalLight::DirectionalLight(const Vector4& diffuse, const Vector4& ambient, const Vector4& specular, const Vector3& direction, int id)
{
	diffuseColor = diffuse;
	ambientColor = ambient;
	specularColor = specular;
	this->direction = direction;
	this->id = id;
};
void DirectionalLight::SetDirectionalLight(Shader* shader)
{
	shader->SetVec3("dirLight[" + std::to_string(id) + "].direction", direction);
	shader->SetVec4("dirLight[" + std::to_string(id) + "].ambient", ambientColor);
	shader->SetVec4("dirLight[" + std::to_string(id) + "].diffuse", diffuseColor);
	shader->SetVec4("dirLight[" + std::to_string(id) + "].specular", specularColor);
}