
#pragma once

#include <unordered_map>
#include <string>
#include <filesystem>
#include <iostream>

#include "dll.h"
#include "Resource.h"
#include "Debug/log.h"


class GOLEM_ENGINE_API ResourceManager
{
private:
	// Static pointer which points to the only instance of this class
	static ResourceManager* m_instancePtr;

	static inline std::string m_defaultShader = "default_shader";
	static inline std::string m_defaultTexture = "default_texture";
	static inline std::string m_defaultModel = "default_model";
	static inline std::string m_terrainShader0 = "default_terrain_shader";    // For black and white gradient
	static inline std::string m_terrainShader1 = "default_terrain_texture_shader";    // For texture
	static inline std::string m_terrainComputeShader = "default_terrain_compute_shader";
	static inline std::string m_defaultGridTerrainTexture = "default_grid_terrain_texture";
	static inline std::string m_sphereColliderShader = "sphere_collider_shader";
	static inline std::string m_boxColliderShader = "box_collider_shader";
	static inline std::string m_skyboxShader = "skybox_shader";

	std::unordered_map<std::string, Resource*> m_resources;
private:
	ResourceManager() {}

public:
	static ResourceManager* GetInstance();
	static void CreateAndLoadResources();

	static std::string GetDefaultShader();
	static std::string GetDefaultTexture();
	static std::string GetDefaultModel();
	static std::string GetTerrainShader();
	static std::string GetTerrainTextureShader();
	static std::string GetTerrainComputeShader();
	static std::string GetGridTerrainTexture();
	static std::string GetSkyboxShader();

	void ProcessFile(const std::filesystem::path& _filePath);
	void TraverseDirectoryAndLoadFiles(const std::filesystem::path& _directoryPath);

	template<class T>
	T* Create(std::string _name, std::string _path);
	template<class T>
	T* Create(std::string _name);
	template<class T>
	T* Get(std::string _name);
	void Delete(std::string _name);

	std::unordered_map<std::string, Resource*> GetResources();
};

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
inline T* ResourceManager::Create(std::string _name)
{
	if (m_resources[_name] != nullptr)
	{
		Delete(_name);
	}
	T* resource = new T;
	m_resources[_name] = resource;
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
