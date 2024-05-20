#pragma once

#include <filesystem>
#include <string>

#include "dll.h"
#include "Resource/resource.h"


class GOLEM_ENGINE_API Texture : public Resource
{
public:
	unsigned int id = 0;
	unsigned int m_width;
	unsigned int m_height;
	std::string name;

public :
	Texture();
	Texture(unsigned int _width, unsigned int _height, unsigned int _format, unsigned int _internalFormat);
	~Texture();

	void Load(const char* _filename);

	void Use();
	void UnUse();
};