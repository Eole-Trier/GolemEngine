#pragma once
#include <vector>
#include "dll.h"
#include "resource.h"

#include <MathsLib/vector2.h>
#include <MathsLib/vector3.h>

struct GOLEM_ENGINE_API Vertex
{
	Vector3 Position;
	Vector3 Normal;
	Vector2 TextureUV;
};

class GOLEM_ENGINE_API Model : public Resource
{
public:
	unsigned int VAO, VBO;

	Model();
	~Model();
	std::vector<Vertex> vertices;
    void Load(const char* modelPath, const char* texturePath);
};

