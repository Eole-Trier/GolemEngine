#pragma once

#include "Resource.h"
#include <unordered_map>
#include <string>

class ResourceManager
{
private:
	std::unordered_map<std::string, Resource*> m_resources;

public:
	ResourceManager() {}
	~ResourceManager() {}

	template<class T>
	T* Create(std::string _name);
	template<class T>
	T* Get(std::string _name);
	void Delete(std::string _name);
};

template<class T>
inline T* ResourceManager::Create(std::string _name)
{
	if (m_resources[_name] != nullptr)
		Delete(_name);
	T* resource = new T;
	m_resources[_name] = resource;
	return resource;
}

template<class T>
inline T* ResourceManager::Get(std::string _name)
{
	return dynamic_cast<T*>(m_resources[_name]);
}

inline void ResourceManager::Delete(std::string _name)
{
	delete m_resources[_name];
	m_resources.erase(_name);
}


