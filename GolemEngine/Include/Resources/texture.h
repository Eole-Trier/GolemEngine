#pragma once

#include <filesystem>
#include "dll.h"

#include "Resources/resource.h"

class GOLEM_ENGINE_API Texture : public Resource
{
public :
	Texture();
	unsigned int id = 0;

	void Load(const char* filename);
};