

#include "Resource/shader.h"
#include "Resource/Light/Directional.h"



DirectionalLight::DirectionalLight(const Vector3& diffuse, const Vector3& ambient, const Vector3& specular, const Vector3& direction, int id)
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
	shader->SetVec3("dirLight[" + std::to_string(id) + "].ambient", ambientColor);
	shader->SetVec3("dirLight[" + std::to_string(id) + "].diffuse", diffuseColor);
	shader->SetVec3("dirLight[" + std::to_string(id) + "].specular", specularColor);
}