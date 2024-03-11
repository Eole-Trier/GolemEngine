#pragma once

#include "dll.h"
#include "Components/Light/Light.h"

class Shader;

class GOLEM_ENGINE_API DirectionalLight : public Light
{
public:
	size_t id;
	Vector3 direction;

	DirectionalLight(const Vector4& diffuse, const Vector4& ambient, const Vector4& specular, const Vector3& direction, 
		const std::vector<DirectionalLight*>& _dirLights, size_t _maxDirs);
	void SetDirectionalLight(Shader* shader);
	
};