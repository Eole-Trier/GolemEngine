#pragma once
#include "Resource/iResource.h"
#include <map>
#include <string>
#include <filesystem>

class ResourcesManager
{
public:

	ResourcesManager() {}
	~ResourcesManager() {}
	template<class T>
	T* Create(std::string _filename);

	void Delete(std::string _filename);
	std::filesystem::path findPath(std::string _filename)
	{
		for (std::filesystem::path file : std::filesystem::recursive_directory_iterator(std::filesystem::current_path()))
			if (file.filename().string().find(_filename) != std::string::npos)
				return file;
		return std::filesystem::path();
	}

private:
	std::map<std::string, IResource*> resources;
};

template<class T>
T* ResourcesManager::Create(std::string _filename)
{
	if (resources[_filename])
	{
		resources[_filename] = new T();
		resources[_filename]->loadFromaPath();
		return (T*)resources[_filename];
	}

	std::filesystem::path pathFile = findPath(_filename);

	if (pathFile == "")
	{
		DEBUG_LOG("File not found : %s", _filename.c_str());
		return nullptr;
	}
	resources[_filename] = new T();
	resources[_filename]->loadResource(pathFile);

	return(T*)resources[_filename];
}

void ResourcesManager::Delete(std::string filename)
{

}