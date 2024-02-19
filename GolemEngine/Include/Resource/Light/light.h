#pragma once

#include "dll.h"
#include <MathsLib/vector3.h>
#include "Resource/resource.h"

class GOLEM_ENGINE_API Light : Resource
{
public:
	Light() {};
	
	Vector3 diffuseColor;
	Vector3 ambientColor;
	Vector3 specularColor;
};