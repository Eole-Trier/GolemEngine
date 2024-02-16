#pragma once

#include "Resource.h"
#include <unordered_map>
#include <string>

class ResourceManager
{
public:
	template<class T>
	T* Create(std::string name);
	template<class T>
	T* Get(std::string name);
	void Delete(std::string name);

private:
	std::unordered_map<std::string, Resource*> mResources;
};

template<class T>
inline T* ResourceManager::Create(std::string name)
{
	if (mResources[name] != nullptr)
		Delete(name);
	T* resource = new T;
	mResources[name] = resource;
	return resource;
}

template<class T>
inline T* ResourceManager::Get(std::string name)
{
	return dynamic_cast<T*>(mResources[name]);
}

inline void ResourceManager::Delete(std::string name)
{
	delete mResources[name];
	mResources.erase(name);
}


