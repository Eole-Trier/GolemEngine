#pragma once

#include <nlohmann/json.hpp>

#include "dll.h"
#include "gameobject.h"
#include "Resource/resourceManager.h"
#include "Resource/guid.h"
#include "Core/camera.h"
#include "Debug/log.h"
#include "Components/Light/light.h"

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
	std::vector<GameObject*> m_gameObjects;

	static constexpr size_t m_maxDirLights = 3;
	static constexpr size_t m_maxPointLights = 10; // According to the shader
	static constexpr size_t m_maxSpotLights = 10;

	std::vector<DirectionalLight*> m_dirLights;
	std::vector<PointLight*> m_pointLights;
	std::vector<SpotLight*> m_spotLights;

public:
	std::string name;
	bool isInit = false;
	bool isObjectInit = false;
	std::string loadingObject;
	
public:
	Scene(std::string _name);

	void Init();
	void InitGameObjects();
	void InitLights();
	void CreateAndLoadResources();
	void Update(float _width, float _height, Camera* _camera);
	void UpdateGameObjects(float _width, float _height, Camera* _camera);
	void UpdateLights(Shader* _shader);
	bool IsNameExists(const std::string& _name);
	
	void AddNewObject(std::string _name, std::string _modelName, std::string _textureName = "", std::string _shaderName = "");
	void AddNewModel(std::string _filePath, std::string _resourceName = "");
	void AddLight(Light* _light);

	
	std::vector<DirectionalLight*> GetDirectionalLights();
	std::vector<PointLight*> GetPointLights();
	std::vector<SpotLight*> GetSpotLights();

	size_t GetMaxDirectionalLights();
	size_t GetMaxPointLights();
	size_t GetMaxSpotLights();

	std::string GetFileName(const std::string& _filePath);
	const std::vector<GameObject*>& GetGameObjects();
	GameObject* GetWorld();

	void AddGameObject(GameObject* _gameObject);
	void RemoveGameObject(GameObject* _gameObject);
	void DeleteLight(Light* _light);

	
	// Define serialization and deserialization functions manually because the
	// macro is not used due to the pointer member variable.
	void to_json(json& j) const
	{
		j = json
		{
			{"name", name},
			{"guid", m_guid.ToString()},
			{"isObjectInit", isObjectInit},
			{"loadingObject", loadingObject}
		};
		if (m_world != nullptr)
		{
			json jWorld;
			m_world->to_json(jWorld);
			j["world"] = jWorld;
		}
		if (!m_gameObjects.empty())
		{
			json jGameObjects;
			for (int i = 0; i < m_gameObjects.size(); i++)
			{
				json jGameObjectPtr;
				m_gameObjects[i]->to_json(jGameObjectPtr);
				jGameObjects.push_back(jGameObjectPtr);
			}
			j["gameObjects"] = jGameObjects;
		}
	}
};