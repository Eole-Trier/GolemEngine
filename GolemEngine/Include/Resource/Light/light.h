#pragma once

#include "dll.h"
#include <MathsLib/vector4.h>
#include "Resource/resource.h"


class GOLEM_ENGINE_API Light : Resource
{
public:
	Light() {};
	
	Vector4 diffuseColor;
	Vector4 ambientColor;
	Vector4 specularColor;
};