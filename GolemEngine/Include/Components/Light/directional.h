#pragma once

#include <vector>

#include <vector3.h>

#include "dll.h"
#include "Components/Light/Light.h"

class Shader;

class GOLEM_ENGINE_API DirectionalLight : public Light
{
public:
	size_t id;
	Vector3 direction;

public:
	DirectionalLight(const Vector4& _diffuse, const Vector4& _ambient, const Vector4& _specular, const Vector3& _direction, 
		const std::vector<DirectionalLight*>& _dirLights, size_t _maxDirs);
	void SetDirectionalLight(Shader* _shader);
	
	void Update() override {};
};