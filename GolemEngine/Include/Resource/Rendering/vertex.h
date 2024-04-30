#pragma once

#include "vector3.h"
#include "vector2.h"


struct GOLEM_ENGINE_API Vertex
{
	Vector3 Position;
	Vector3 Normal;
	Vector2 TextureCoords;
};