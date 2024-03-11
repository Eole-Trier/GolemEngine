#include <vector>

#include "Debug/log.h"
#include "Resource/Rendering/shader.h"
#include "Components/Light/Directional.h"



DirectionalLight::DirectionalLight(const Vector4& diffuse, const Vector4& ambient, const Vector4& specular, const Vector3& direction, 
	const std::vector<DirectionalLight*>& _dirLights, size_t _maxDirs)
{
	diffuseColor = diffuse;
	ambientColor = ambient;
	specularColor = specular;
	Matrix4 m = Matrix4(4);
	this->direction = direction;
	id = _dirLights.size();
	if (id >= (size_t)_maxDirs)
	{
		Log::Print("The Directional light %d will not be used. Directional lights limit : %d", id, _maxDirs);
	}
};
void DirectionalLight::SetDirectionalLight(Shader* shader)
{
	shader->SetVec3("dirLight[" + std::to_string(id) + "].direction", direction);
	shader->SetVec4("dirLight[" + std::to_string(id) + "].ambient", ambientColor);
	shader->SetVec4("dirLight[" + std::to_string(id) + "].diffuse", diffuseColor);
	shader->SetVec4("dirLight[" + std::to_string(id) + "].specular", specularColor);
}