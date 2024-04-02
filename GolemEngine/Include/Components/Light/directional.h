#pragma once

#include <vector>

#include <vector3.h>

#include "dll.h"
#include "Components/Light/Light.h"
#include "Refl/refl.hpp"

class Shader;

class GOLEM_ENGINE_API DirectionalLight : public Light
{
public:
	size_t id;
	Vector3 direction;

public:
	DirectionalLight();
	DirectionalLight(const Vector4& _diffuse, const Vector4& _ambient, const Vector4& _specular, const Vector3& _direction);
	~DirectionalLight();
	void SetDirectionalLight(Shader* _shader);
	
	void Update(Shader* _shader) override;
};

REFL_AUTO(
	type(DirectionalLight, bases<Light>),
	field(direction)
)