#include "Core/scene.h"

#include <filesystem>
#include <nlohmann/json.hpp>

#include "utils.h"
#include "Core/gameobject.h"
#include "Resource/Rendering/mesh.h"
#include "Resource/Rendering/shader.h"
#include "Resource/Rendering/texture.h"
#include "Resource/Rendering/model.h"
#include "Resource/resourceManager.h"
#include "Resource/sceneManager.h"
#include "Resource/tools.h"
#include "Components/Light/directionalLight.h"
#include "Components/Light/pointLight.h"
#include "Components/Light/spotLight.h"
#include "Components/transform.h"
#include "Components/meshRenderer.h"
#include "Components/audio.h"

using json = nlohmann::json;


Scene::Scene(std::string _name, bool _isEmpty)
    : name(_name)
{
    SceneManager::SetCurrentScene(this);
    
    m_world = new GameObject("World", new Transform(Vector3(0, 0, 0), Vector3(0), Vector3(1), nullptr));
    
    if (!_isEmpty)
    { 
        Init();
    }
}

void Scene::Init()
{
    InitGameObjects();
    InitLights();
}

void Scene::InitGameObjects()
{
    ResourceManager* resourceManager = ResourceManager::GetInstance();
    Shader* defaultShader = resourceManager->Get<Shader>(ResourceManager::GetDefaultShader());
    
    std::string vikingName = "viking";
    Transform* vikingTransform = new Transform(Vector3(0, 0, 0), Vector3(0), Vector3(1), m_world->transform);
    GameObject* vikingGo = new GameObject(vikingName, vikingTransform);
    Texture* vikingText = resourceManager->Get<Texture>("viking_texture");
    Model* vikingRoom = resourceManager->Get<Model>("viking_room");
    Mesh* vikingMesh = new Mesh(vikingRoom, vikingText, defaultShader);
    vikingGo->AddComponent(new MeshRenderer(vikingMesh));

    Audio* audio1 = new Audio("music_01.wav");
    vikingGo->AddComponent(audio1);

    std::string ballBaldName = "ball_bald";
    Transform* ballBaldTransform = new Transform(Vector3(3, 0, 0), Vector3(0), Vector3(1), m_world->transform);
    GameObject* ballBaldGo = new GameObject(ballBaldName, ballBaldTransform);
    Texture* ballBaldTexture = resourceManager->Get<Texture>("all_bald_texture");
    Model* ballBald = resourceManager->Get<Model>("sphere");
    Mesh* ballBaldMesh = new Mesh(ballBald, ballBaldTexture, defaultShader);
    ballBaldGo->AddComponent(new MeshRenderer(ballBaldMesh));

    std::string ballBaldName2 = "ball_bald2";
    Transform* ballBaldTransform2 = new Transform(Vector3(-3, 0, 0), Vector3(0), Vector3(1), m_world->transform);
    GameObject* ballBald2Go = new GameObject(ballBaldName2, ballBaldTransform2);
    Texture* ballBaldTexture2 = resourceManager->Get<Texture>("all_bald_texture");
    Model* ballBald2 = resourceManager->Get<Model>("sphere");
    Mesh* ballBaldMesh2 = new Mesh(ballBald2, ballBaldTexture2, defaultShader);
    ballBald2Go->AddComponent(new MeshRenderer(ballBaldMesh2));
}

void Scene::InitLights()
{
    // Set up directional light
    DirectionalLight* dir = new DirectionalLight;
    m_world->AddComponent(dir);
}

void Scene::Update(float _width, float _height, Camera* _camera)
{
    ResourceManager* resourceManager = ResourceManager::GetInstance();
    Shader* defaultShader = resourceManager->Get<Shader>(ResourceManager::GetDefaultShader());
    defaultShader->Use();
    defaultShader->SetViewPos(_camera->m_position);

    if (!m_terrains.empty())
    {
        UpdateTerrains(_camera); 
    }
    UpdateGameObjects(_width, _height, _camera);
    UpdateLights(defaultShader);
}

void Scene::UpdateGameObjects(float _width, float _height, Camera* _camera)
{
    // Drag and drop
    if (isNewObjectDropped)
    {
        CreateNewObject(loadingObject.c_str(), loadingObject.c_str());
        isNewObjectDropped = false;
    }

    m_world->transform->UpdateSelfAndChilds();

    for (int i = 0; i < gameObjects.size(); i++)
    {
        if (MeshRenderer* meshRenderer = gameObjects[i]->GetComponent<MeshRenderer>())
        {
            meshRenderer->Draw(_width, _height, _camera);
        }
        
        if (Audio* audio = gameObjects[i]->GetComponent<Audio>())
        {
            audio->Update();
        }
    }
}

void Scene::UpdateLights(Shader* _shader)
{
    _shader->Use();

    _shader->SetInt("nbrDirLights", m_dirLights.size());
    _shader->SetInt("nbrPointLights", m_pointLights.size());
    _shader->SetInt("nbrSpotLights", m_spotLights.size());

    for (unsigned int i = 0; i < m_dirLights.size(); ++i)
    {
        m_dirLights[i]->Update(_shader);
    }
    for (unsigned int i = 0; i < m_pointLights.size(); ++i)
    {
        m_pointLights[i]->Update(_shader);
    }
    for (unsigned int i = 0; i < m_spotLights.size(); ++i)
    {
        m_spotLights[i]->Update(_shader);
    }
}

void Scene::UpdateTerrains(Camera* _camera)
{
    for (int i = 0; i < m_terrains.size(); i++)
    {
        m_terrains[i]->Draw(_camera);
    }
}

// Check the gameobject's name is already in the vector or not.
// If it exists will give a new name with a _2 at the last
bool Scene::IsNameExists(const std::string& _name)
{
    for (int i = 0; i < gameObjects.size(); i++)
    {
        if (gameObjects[i]->name == _name)
        {
            return true;
        }
    }
    return false;

}

void Scene::AddLight(Light* _light)
{
    // TODO remove and put in lights
    if (PointLight* pL = dynamic_cast<PointLight*>(_light))
    {
        m_pointLights.push_back(pL);
    }
    else if (SpotLight* sL = dynamic_cast<SpotLight*>(_light))
    {
        m_spotLights.push_back(sL);

    }
    else if (DirectionalLight* dL = dynamic_cast<DirectionalLight*>(_light))
    {
        m_dirLights.push_back(dL);
    }
}

void Scene::AddGameObject(GameObject* _gameObject)
{
    // TODO maybe remove and put it in gamobject constructor
    gameObjects.push_back(_gameObject);
}

void Scene::RemoveGameObject(GameObject* _gameObject)
{
    bool removed = false;
    for (size_t i = 0; i < gameObjects.size(); i++)
    {
        if (gameObjects[i] == _gameObject)
        {
            removed = true;
        }
        if (removed)
        {
            gameObjects[i]->SetId(i - 1);
        }
    }
    std::erase(gameObjects, _gameObject);
}

void Scene::DeleteLight(Light* _light)
{
    if (PointLight* pL = dynamic_cast<PointLight*>(_light))
    {
        std::erase(m_pointLights, pL);
    }
    else if (SpotLight* sL = dynamic_cast<SpotLight*>(_light))
    {
        std::erase(m_spotLights, sL);
    }
    else if (DirectionalLight* dL = dynamic_cast<DirectionalLight*>(_light))
    {
        std::erase(m_dirLights, dL);
    }
}

void Scene::AddTerrain(Terrain* _terrain)
{
    m_terrains.push_back(_terrain);
}

// To add a new gameobject in the scene
void Scene::CreateNewObject(std::string _name, std::string _modelName, std::string _textureName, std::string _shaderName)
{
    ResourceManager* resourceManager = ResourceManager::GetInstance();

    std::string name = _name;
    Transform* transform = new Transform(Vector3(1), Vector3(0), Vector3(1), m_world->transform);
    Texture* texture;
    Shader* shader;

    if (_textureName.empty())
    {
        texture = resourceManager->Get<Texture>(ResourceManager::GetDefaultTexture());
    }
    else
    {
        texture = resourceManager->Get<Texture>(_textureName);
    }

    if (_shaderName.empty())
    {
        shader = resourceManager->Get<Shader>(ResourceManager::GetDefaultShader());
    }
    else
    {
        shader = resourceManager->Get<Shader>(_shaderName);
    }

    // Using the rename functions
    int suffix = 2; // start at 2 because of two objects having the same name
    std::string originalName = name;
    while (IsNameExists(name))
    {
        name = originalName + "_" + std::to_string(suffix++);
    }

    Model* model = resourceManager->Get<Model>(_modelName);
    Mesh* mesh = new Mesh(model, texture, shader);
    GameObject* go = new GameObject(name, transform);
    go->AddComponent(new MeshRenderer(mesh));
    AddGameObject(go);
}

void Scene::CreateNewModel(std::string _filePath, std::string _resourceName)
{
    ResourceManager* resourceManager = ResourceManager::GetInstance();

    bool hasDuplicate = false;
    for (const auto& pair : resourceManager->GetResources())
    {
        if (pair.first == GetFileName(_filePath))
        {
            hasDuplicate = true;
            loadingObject = GetFileName(_filePath);
            break;
        }
    }

    if (hasDuplicate)
    {
        std::cout << "Resource with name " << _resourceName << " already exists." << std::endl;
        return;
    }

    if (_resourceName == "")
    {
        Model* model = resourceManager->Get<Model>(ResourceManager::GetDefaultModel());
        loadingObject = GetFileName(_filePath);
    }
    else
    {
        Model* model = resourceManager->Get<Model>(_resourceName);
        loadingObject = GetFileName(_filePath);
    }
}

std::vector<DirectionalLight*> Scene::GetDirectionalLights()
{
    return m_dirLights;
}

std::vector<PointLight*> Scene::GetPointLights()
{
    return m_pointLights;
}

std::vector<SpotLight*> Scene::GetSpotLights()
{
    return m_spotLights;
}

std::vector<Terrain*> Scene::GetTerrains()
{
    return  m_terrains;
}

size_t Scene::GetMaxDirectionalLights()
{
    return m_maxDirLights;
}

size_t Scene::GetMaxPointLights()
{
    return m_maxPointLights;
}

size_t Scene::GetMaxSpotLights()
{
    return m_maxSpotLights;
}

std::string Scene::GetFileName(const std::string& _filePath)
{
    std::filesystem::path path(_filePath);
    return path.stem().string();
}

GameObject* Scene::GetWorld()
{
    return m_world;
}

Guid Scene::GetGuid()
{
    return  m_guid;
}

void Scene::SetGuid(Guid _guid)
{
    m_guid = _guid;
}


