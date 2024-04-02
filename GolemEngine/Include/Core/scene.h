#pragma once

#include "dll.h"
#include "Resource/resourceManager.h"
#include "Core/camera.h"
#include "Debug/log.h"

class DirectionalLight;
class PointLight;
class SpotLight;
class Shader;
class GameObject;
class Mesh;

class GOLEM_ENGINE_API Scene
{
private:
	
	GameObject* m_world;
	std::vector<GameObject*> m_gameObjects;
	std::vector<Mesh*> m_meshes;

	static constexpr size_t m_maxDirLights = 1;
	static constexpr size_t m_maxPointLights = 10; // According to the shader
	static constexpr size_t m_maxSpotLights = 10;

	std::vector<DirectionalLight*> m_dirLights;
	std::vector<PointLight*> m_pointLights;
	std::vector<SpotLight*> m_spotLights;

public:
	std::string name;
	bool isInit = false;
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
	void DeleteGameObject(GameObject* _gameObject);
	void CreateGameObject(GameObject* _owner);
	void AddNewObject(std::string _name, std::string _modelName, std::string _textureName = "", std::string _shaderName = "");
	void AddNewModel(std::string _filePath, std::string _resourceName = "");
	
	Mesh* GetMeshByName(std::string _name);
	std::string GetFileName(const std::string& _filePath);
	const std::vector<GameObject*>& GetGameObjects();
	GameObject* GetWorld();

};