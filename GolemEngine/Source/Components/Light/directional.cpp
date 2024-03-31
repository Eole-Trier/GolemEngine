#include "Components/Light/Directional.h"

#include "Debug/log.h"
#include "Resource/Rendering/shader.h"

DirectionalLight::DirectionalLight(const Vector4& _diffuse, const Vector4& _ambient, const Vector4& _specular, const Vector3& _direction, 
	const std::vector<DirectionalLight*>& _dirLights, size_t _maxDirs)
	: Light(_diffuse, _ambient, _specular), direction(_direction)
{
	id = _dirLights.size();
	if (id >= _maxDirs)
	{
		Log::Print("The Directional light %d will not be used. Directional lights limit : %d", id, _maxDirs);
	}
};
void DirectionalLight::SetDirectionalLight(Shader* _shader)
{
	_shader->SetVec3("dirLights[" + std::to_string(id) + "].direction", direction);
	_shader->SetVec4("dirLights[" + std::to_string(id) + "].ambient", ambientColor);
	_shader->SetVec4("dirLights[" + std::to_string(id) + "].diffuse", diffuseColor);
	_shader->SetVec4("dirLights[" + std::to_string(id) + "].specular", specularColor);
}

void DirectionalLight::Update(Shader* _shader)
{
	SetDirectionalLight(_shader);
}
