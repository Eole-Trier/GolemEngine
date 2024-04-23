#pragma once

#include <nlohmann/json.hpp>

#include "dll.h"
#include "gameobject.h"
#include "Resource/resourceManager.h"
#include "Resource/guid.h"
#include "Core/camera.h"
#include "Debug/log.h"
#include "Components/Light/light.h"
#include "WorldBuilder/terrain.h"

using json = nlohmann::json;

class DirectionalLight;
class PointLight;
class SpotLight;
class Shader;
class GameObject;
class Mesh;


class GOLEM_ENGINE_API Scene
{
private:
	Guid m_guid;
	GameObject* m_world = nullptr;

	static constexpr size_t m_maxDirLights = 3;
	static constexpr size_t m_maxPointLights = 10;    // According to the shader
	static constexpr size_t m_maxSpotLights = 10;

	std::vector<DirectionalLight*> m_dirLights;
	std::vector<PointLight*> m_pointLights;
	std::vector<SpotLight*> m_spotLights;
	std::vector<Mesh*> m_meshes;

	std::vector<Terrain*> m_terrains;

public:
	std::string name;
	std::vector<GameObject*> gameObjects;
	bool isNewObjectDropped = false;
	std::string loadingObject;
	
public:
	// Create a scene by giving it a name and setting _isEmpty to 0 or 1. 0 means the scene will be a default
	// scene with a few objects to start, 1 means the scene will have nothing in it (useful for creating scenes from files)
	Scene(std::string _name, bool _isEmpty);

	void InitDefaultScene();
	void Update(Camera* _camera);
	void UpdateTerrains(Camera* _camera);
	void UpdateGameObjects(Camera* _camera);
	void UpdateLights(Shader* _shader);
	// Check the gameobject's name is already in the vector or not.
	bool IsNameExists(const std::string& _name);
	// To add a new gameobject in the scene
	void AddTerrain(Terrain* _terrain);
	void CreateNewObject(std::string _name, std::string _modelName, std::string _textureName = "", std::string _shaderName = "");
	void CreateNewModel(std::string _filePath, std::string _resourceName = "");
	void RemoveGameObject(GameObject* _gameObject);
	void AddLight(Light* _light);
	void DeleteLight(Light* _light);
	
	std::vector<Terrain*> GetTerrains();
	std::vector<DirectionalLight*> GetDirectionalLights();
	std::vector<PointLight*> GetPointLights();
	std::vector<SpotLight*> GetSpotLights();
	size_t GetMaxDirectionalLights();
	size_t GetMaxPointLights();
	size_t GetMaxSpotLights();
	std::string GetFileName(const std::string& _filePath);
	GameObject* GetWorld();
	Guid GetGuid();

	void SetGuid(Guid _guid);

	
	// Define serialization and deserialization functions manually because the
	// macro is not used due to the pointer member variable.
	void ToJson(json& _j) const
	{
		_j = json
		{
			{"name", name},
			{"guid", m_guid.ToString()},
		};
		if (!gameObjects.empty())
		{
			std::cout << "Game object size: " << gameObjects.size() << std::endl;
			json jGameObjects;
			for (int i = 0; i < gameObjects.size(); i++)
			{
				json jGameObjectPtr;
				gameObjects[i]->ToJson(jGameObjectPtr);
				jGameObjects.push_back(jGameObjectPtr);
			}
			_j["gameObjects"] = jGameObjects;
		}
	}
};