#pragma once

#include <vector>

#include "dll.h"
#include "Resource/resource.h"
#include "vertex.h"

class GOLEM_ENGINE_API Model : public Resource
{
public:
	unsigned int VAO, VBO;
	std::vector<Vertex> vertices;

public:

	Model();
	~Model();

    void Load(const char* _modelPath);
};

