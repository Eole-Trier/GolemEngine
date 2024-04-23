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


	// Define serialization and deserialization functions manually because the
	// macro is not used due to the pointer member variable.
	void ToJson(json& j) const override
	{
		j = json
		{
			{"name", "directionalLight"},
			{"data",
				{
					{"id", id},
					{"diffuseColor", diffuseColor},
					{"ambientColor", ambientColor},
					{"specularColor", specularColor},
					{"direction", direction}
				}
			}
		};
	}
};

REFL_AUTO(
	type(DirectionalLight, bases<Light>),
	field(direction)
)