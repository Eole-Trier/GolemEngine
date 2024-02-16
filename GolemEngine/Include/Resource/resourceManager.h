#pragma once
#include "Resource/iResource.h"

#include <map>
#include <string>
#include <filesystem>

class ResourceManager
{
private:
	std::map<std::string, IResource*> resources;

public:

	ResourceManager() {}
	~ResourceManager() {}

	template<class T>
	T* Create(std::string _filename);

	void Delete(std::string* _filename);

	std::filesystem::path FindPath(std::string _filename)
	{
		for (std::filesystem::path file : std::filesystem::recursive_directory_iterator(std::filesystem::current_path()))
		{
			if (file.filename().string().find(_filename) != std::string::npos)
			{
				return file;
			}
		}
		return std::filesystem::path();
	}
};

template<class T>
T* ResourceManager::Create(std::string _filename)
{
	if (resources[_filename])
	{
		resources[_filename] = new T();
		resources[_filename]->loadFromaPath();
		return (T*)resources[_filename];
	}

	std::filesystem::path pathFile = FindPath(_filename);

	if (pathFile == "")
	{
		std::cout << "File not found : " << _filename << std::endl;
		return nullptr;
	}
	resources[_filename] = new T();
	resources[_filename]->loadResource(pathFile);

	return(T*)resources[_filename];
}

void ResourceManager::Delete(std::string* _filename)
{
	// TO CHECK
	_filename = nullptr;
	delete _filename;
}