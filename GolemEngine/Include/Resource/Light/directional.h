#pragma once

#include "dll.h"
#include "Resource/Light/Light.h"

class Shader;

class GOLEM_ENGINE_API DirectionalLight : public Light
{
public:
	int id;
	Vector3 direction;

	DirectionalLight(const Vector3& diffuse, const Vector3& ambient, const Vector3& specular, const Vector3& direction, int id);
	void SetDirectionalLight(Shader* shader);
	
};