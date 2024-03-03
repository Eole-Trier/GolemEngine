#pragma once

#include <filesystem>
#include <string>

#include "dll.h"
#include "resource.h"

class GOLEM_ENGINE_API Texture : public Resource
{
public:
	unsigned int id = 0;
	std::string name;
	std::string path;

public :
	Texture();
	~Texture();

	void Load(const char* _filename);
	void Use();
};