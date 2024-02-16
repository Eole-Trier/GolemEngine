#pragma once
#include <vector>

#include "dll.h"
#include "resource.h"
#include "vector2.h"
#include "vector3.h"
#include "vertex.h"


class GOLEM_ENGINE_API Model : public Resource
{
public:
	unsigned int VAO, VBO;

	Model();
	~Model();
	std::vector<Vertex> vertices;
    void Load(const char* modelPath, const char* texturePath);
};

