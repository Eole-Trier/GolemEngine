#pragma once

#include "dll.h"

#include "Resource/resource.h"
#include "Components/component.h"

#include <vector4.h>

class GOLEM_ENGINE_API Light : Component
{
public:
	Vector4 diffuseColor;
	Vector4 ambientColor;
	Vector4 specularColor;

public:
	Light(const Vector4& _diffuse, const Vector4& _ambient, const Vector4& _specular);
};