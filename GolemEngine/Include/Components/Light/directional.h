#pragma once

#include "dll.h"
#include "Components/Light/Light.h"

class Shader;

class GOLEM_ENGINE_API DirectionalLight : public Light
{
public:
	int id;
	Vector3 direction;

	DirectionalLight(const Vector4& diffuse, const Vector4& ambient, const Vector4& specular, const Vector3& direction, int id);
	void SetDirectionalLight(Shader* shader);
	
};