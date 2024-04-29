#include "Core/scene.h"

#include <filesystem>
#include <nlohmann/json.hpp>

#include "golemEngine.h"
#include "utils.h"
#include "Core/mesh.h"
#include "Resource/Rendering/model.h"
#include "Resource/Rendering/texture.h"
#include "Resource/Rendering/shader.h"
#include "Utils/tools.h"
#include "Components\Light\pointLight.h"
#include "Components\Light\directionalLight.h"
#include "Components\Light\spotLight.h"
#include "Resource/Rendering/shader.h"
#include "Core/gameobject.h"
#include "Resource/resourceManager.h"
#include "Resource/sceneManager.h"
#include "Components/transform.h"
#include "Components/meshRenderer.h"
#include "Components/audio.h"
#include "Physic/physicSystem.h"
#include "Components/Physic/sphereCollider.h"
#include "Components/Physic/boxCollider.h"
#include "Wrappers/windowWrapper.h"

using json = nlohmann::json;

Scene::Scene(std::string _name, bool _isEmpty)
    : name(_name)
{
    SceneManager::SetCurrentScene(this);
    ResourceManager::CreateAndLoadResources();
    m_world = new GameObject("World", new Transform(Vector3(0, 0, 0), Vector3(0), Vector3(1), nullptr));
    InitLights();

    
    if (!_isEmpty)    // If there is already a save of the world, don't init a default scene
    { 
        InitDefaultScene();
    }
}

void Scene::InitDefaultScene()
{
    ResourceManager* resourceManager = ResourceManager::GetInstance();
    Shader* defaultShader = resourceManager->Get<Shader>(ResourceManager::GetDefaultShader());

    // Create a viking room model
    std::string vikingName = "viking";
    Transform* vikingTransform = new Transform(Vector3(0, 0, -5), Vector3(0), Vector3(1), m_world->transform);
    GameObject* vikingGo = new GameObject(vikingName, vikingTransform);
    Texture* vikingText = resourceManager->Get<Texture>("viking_room.jpg");
    Model* vikingRoom = resourceManager->Get<Model>("viking_room.obj");
    Mesh* vikingMesh = new Mesh(vikingRoom, vikingText, defaultShader);
    vikingGo->AddComponent(new MeshRenderer(vikingMesh));
    BoxCollider* box = new BoxCollider(Vector3(1.f));
    vikingGo->AddComponent(box);
    box->Begin();
    Audio* audio1 = new Audio("music_01.wav");
    vikingGo->AddComponent(audio1);

    // Create a sphere model
    std::string ballBaldName = "ball_bald";
    Transform* ballBaldTransform = new Transform(Vector3(0, 10, -5), Vector3(0), Vector3(1), m_world->transform);
    GameObject* ballBaldGo = new GameObject(ballBaldName, ballBaldTransform);
    Texture* ballBaldTexture = resourceManager->Get<Texture>("all_bald.jpg");
    Model* ballBald = resourceManager->Get<Model>("sphere.obj");
    Mesh* ballBaldMesh = new Mesh(ballBald, ballBaldTexture, defaultShader);
    ballBaldGo->AddComponent(new MeshRenderer(ballBaldMesh));
    SphereCollider* sc = new SphereCollider(1.f);
    ballBaldGo->AddComponent(sc);
    sc->Begin();

    std::string ballBaldName2 = "ball_bald2";
    Transform* ballBaldTransform2 = new Transform(Vector3(-3, 0, 0), Vector3(0), Vector3(1), m_world->transform);
    GameObject* ballBald2Go = new GameObject(ballBaldName2, ballBaldTransform2);
    Texture* ballBaldTexture2 = resourceManager->Get<Texture>("all_bald.jpg");
    Model* ballBald2 = resourceManager->Get<Model>("sphere.obj");
    Mesh* ballBaldMesh2 = new Mesh(ballBald2, ballBaldTexture2, defaultShader);
    ballBald2Go->AddComponent(new MeshRenderer(ballBaldMesh2));
}

void Scene::InitLights()
{
    // Set up directional light
    DirectionalLight* dir = new DirectionalLight;
    m_world->AddComponent(dir);
}

void Scene::Update(Camera* _camera, float _width, float _height)
{
    ResourceManager* resourceManager = ResourceManager::GetInstance();
    Shader* defaultShader = resourceManager->Get<Shader>(ResourceManager::GetDefaultShader());
    defaultShader->Use();
    defaultShader->SetViewPos(_camera->position);

    if (!m_terrains.empty())
    {
        UpdateTerrains(_camera); 
    }
    
    UpdateGameObjects(_camera, _width, _height);    // Always at least one gameobject (world)

    if (!m_dirLights.empty() || !m_pointLights.empty() || !m_spotLights.empty())
    {
        UpdateLights(defaultShader);
    }
}

void Scene::UpdateTerrains(Camera* _camera)
{
    for (int i = 0; i < m_terrains.size(); i++)
    {
        m_terrains[i]->Draw(_camera);
    }
}

void Scene::UpdateGameObjects(Camera* _camera, float _width, float _height)
{
    // Drag and drop
    if (isNewObjectDropped)
    {
        CreateNewObject(loadingObject.c_str(), loadingObject.c_str());
        isNewObjectDropped = false;
    }

    m_world->transform->UpdateSelfAndChilds();


    PhysicSystem::Update();

    for (int i = 0; i < gameObjects.size(); i++)
    {
        gameObjects[i]->Update();
        if (MeshRenderer* meshRenderer = gameObjects[i]->GetComponent<MeshRenderer>())
            meshRenderer->Draw(_width, _height, _camera);
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
        m_dirLights[i]->SetDirectionalLight(_shader);
    }
    for (unsigned int i = 0; i < m_pointLights.size(); ++i)
    {
        m_pointLights[i]->SetPointLight(_shader);
    }
    for (unsigned int i = 0; i < m_spotLights.size(); ++i)
    {
        m_spotLights[i]->SetSpotLight(_shader);
    }
}

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

void Scene::AddTerrain(Terrain* _terrain)
{
    m_terrains.push_back(_terrain);
}

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
    while (IsNameExists(name))    // If an object already has the same name, add "_[suffix]" to it to make new name
    {
        name = originalName + "_" + std::to_string(suffix++);
    }

    Model* model = resourceManager->Get<Model>(_modelName);
    Mesh* mesh = new Mesh(model, texture, shader);
    GameObject* gameObject = new GameObject(name, transform);
    gameObject->AddComponent(new MeshRenderer(mesh));
    gameObjects.push_back(gameObject);
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

std::vector<Terrain*> Scene::GetTerrains()
{
    return  m_terrains;
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


