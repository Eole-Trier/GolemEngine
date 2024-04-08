#pragma once

#include <filesystem>
#include <string>

#include "dll.h"
#include "Resource/resource.h"
#include "Wrappers/graphicWrapper.h"


class GOLEM_ENGINE_API Texture : public Resource
{
public:
	unsigned int id = 0;
	unsigned int m_width;
	unsigned int m_height;
	std::string name;
	std::string path;

public :
	Texture();
	Texture(unsigned int _width, unsigned int _height, unsigned int _format);
	~Texture();

	//static void Create(unsigned int _width, unsigned int _height);

	void Load(const char* _filename);

	void Use();
};