#pragma once

#include "dll.h"

#include <vector4.h>

#include "Resource/resource.h"
#include "Components/component.h"
#include "Resource/Rendering/shader.h"
#include "Refl/refl.hpp"


class GOLEM_ENGINE_API Light : public Component
{
public:
	Vector4 diffuseColor;
	Vector4 ambientColor;
	Vector4 specularColor;

public:
	Light() = default;
	Light(const Vector4& _diffuse, const Vector4& _ambient, const Vector4& _specular);
	virtual ~Light();
	virtual void Update(Shader* _shader) = 0;
};

REFL_AUTO(
    type(Light, bases<Component>),
    field(diffuseColor),
	field(ambientColor),
	field(specularColor)
)