#pragma once

#include "dll.h"
#include <MathsLib/vector4.h>
#include "Resource/resource.h"
#include "Components/component.h"

class GOLEM_ENGINE_API Light : Component
{
public:
	Light() {};
	
	Vector4 diffuseColor;
	Vector4 ambientColor;
	Vector4 specularColor;
};