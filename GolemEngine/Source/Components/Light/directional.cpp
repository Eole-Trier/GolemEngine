#include "Components/Light/Directional.h"

#include "Debug/log.h"
#include "Resource/Rendering/shader.h"
#include "Resource/sceneManager.h"

DirectionalLight::DirectionalLight()
{
	std::vector<DirectionalLight*> dirLights = SceneManager::GetCurrentScene()->GetDirectionalLights();
	size_t maxDirs = SceneManager::GetCurrentScene()->GetMaxDirectionalLights();

	diffuseColor = Vector4(1.f, 1.f, 1.f, 1.f);
	ambientColor = Vector4(1.f, 1.f, 1.f, 1.f);
	specularColor = Vector4(1.f, 1.f, 1.f, 1.f);
	direction = Vector3(0.f, 0.f, 0.f);

	id = dirLights.size();
	if (id >= maxDirs)
	{
		Log::Print("The DirectionalLight %d will not be used. DirectionalLights limit : %d", id, maxDirs);
	}
	else
	{
		SceneManager::GetCurrentScene()->AddLight(this);
	}
};

DirectionalLight::DirectionalLight(const Vector4& _diffuse, const Vector4& _ambient, const Vector4& _specular, const Vector3& _direction)
	: Light(_diffuse, _ambient, _specular), direction(_direction)
{
	std::vector<DirectionalLight*> dirLights = SceneManager::GetCurrentScene()->GetDirectionalLights();
	size_t maxDirs = SceneManager::GetCurrentScene()->GetMaxDirectionalLights();

	id = dirLights.size();
	if (id >= maxDirs)
	{
		Log::Print("The DirectionalLight %d will not be used. DirectionalLights limit : %d", id, maxDirs);
	}
	else
	{
		SceneManager::GetCurrentScene()->AddLight(this);
	}
};

DirectionalLight::~DirectionalLight()
{
	SceneManager::GetCurrentScene()->DeleteLight(this);
}

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
