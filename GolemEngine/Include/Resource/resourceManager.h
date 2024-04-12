#pragma once

#include <unordered_map>
#include <string>
#include <iostream>

#include "dll.h"
#include "Resource.h"
#include "Debug/log.h"


class GOLEM_ENGINE_API ResourceManager
{
private:
	// Static pointer which points to the only instance of this class
	static ResourceManager* m_instancePtr;

	std::unordered_map<std::string, Resource*> m_resources;
private:
	ResourceManager() {}

public:
	static ResourceManager* GetInstance()
	{
		if (!m_instancePtr) 
		{
			m_instancePtr = new ResourceManager();
		}
		return m_instancePtr;
	}

	template<class T>
	T* Create(std::string _name, std::string _path);
	template<class T>
	T* Get(std::string _name);
	void Delete(std::string _name);

	std::unordered_map<std::string, Resource*> GetResources();
};
//
template<class T>
inline T* ResourceManager::Create(std::string _name, std::string _path)
{
	if (m_resources[_name] != nullptr)
	{
		Delete(_name);
	}
	T* resource = new T;
	m_resources[_name] = resource;
	m_resources[_name]->path = _path;
	return resource;
}

template<class T>
inline T* ResourceManager::Get(std::string _name)
{
	if (!m_resources[_name])
	{
		Log::Print("No resource of name '%s' exists", _name.c_str());
		return nullptr;
	}
	return dynamic_cast<T*>(m_resources[_name]);
}

inline void ResourceManager::Delete(std::string _name)
{
	delete m_resources[_name];
	m_resources.erase(_name);
}

inline std::unordered_map<std::string, Resource*> ResourceManager::GetResources()
{
	return m_resources;
}


