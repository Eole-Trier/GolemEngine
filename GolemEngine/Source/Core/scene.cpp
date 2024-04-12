#include "Core/scene.h"

#include <filesystem>
#include <nlohmann/json.hpp>

#include "utils.h"
#include "Resource/resourceManager.h"
#include "Resource/Rendering/mesh.h"
#include "Resource/Rendering/model.h"
#include "Resource/Rendering/texture.h"
#include "Resource/Rendering/shader.h"
#include "Resource/tools.h"
#include "..\..\Include\Components\Light\pointLight.h"
#include "..\..\Include\Components\Light\directionalLight.h"
#include "..\..\Include\Components\Light\spotLight.h"
#include "Resource/Rendering/shader.h"
#include "Core/gameobject.h"
#include "Components/transform.h"
#include "Components/meshRenderer.h"
#include "Resource/sceneManager.h"

using json = nlohmann::json;


Scene::Scene(std::string _name)
    : name(_name)
{
    SceneManager::m_currentScene = this;
    Init();
}

void Scene::Init()
{
    //CreateAndLoadResources();
    InitGameObjects();
    InitLights();
}

void Scene::InitLights()
{
    // Set up directional light
    DirectionalLight* dir = new DirectionalLight;
    m_world->AddComponent(dir);
}

void Scene::InitGameObjects()
{
    ResourceManager* resourceManager = ResourceManager::GetInstance();
    m_world = new GameObject("World", new Transform(Vector3(0, 0, 0), Vector3(0), Vector3(1), nullptr));

    Shader* defaultShader = resourceManager->Get<Shader>(SceneManager::m_defaultShader);

    std::string vikingName = "viking";
    Transform* vikingTransform = new Transform(Vector3(0, 0, 0), Vector3(0), Vector3(1), m_world->transform);
    GameObject* vikingGo = new GameObject(vikingName, vikingTransform);
    Texture* viking_text = resourceManager->Get<Texture>("viking_texture");
    Model* viking_room = resourceManager->Get<Model>("viking_room");
    Mesh* vikingMesh = new Mesh(viking_room, viking_text, defaultShader);
    vikingGo->AddComponent(new MeshRenderer(vikingMesh));
    
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

void Scene::Update(float _width, float _height, Camera* _camera)
{
    ResourceManager* resourceManager = ResourceManager::GetInstance();
   
    Shader* shader = resourceManager->Get<Shader>(SceneManager::m_defaultShader);
    shader->Use();

    shader->SetViewPos(_camera->m_position);

    UpdateLights(shader);
    UpdateGameObjects(_width, _height, _camera);
}

void Scene::UpdateGameObjects(float _width, float _height, Camera* _camera)
{
    std::string folderName = "Saves"; 
    std::vector<std::filesystem::path> foundPaths;
    std::filesystem::path currentPath = std::filesystem::current_path();

    // Dragndrop
    if (isDropNewObject)
    {
        CreateNewObject(loadingObject.c_str(), loadingObject.c_str());
        isDropNewObject = false;
    }

    m_world->transform->UpdateSelfAndChilds();

    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        if (MeshRenderer* meshRenderer = m_gameObjects[i]->GetComponent<MeshRenderer>())
        {
            meshRenderer->Draw(_width, _height, _camera);
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



void Scene::AddGameObject(GameObject* _gameObject)
{
    // TODO maybe remove and put it in gamobject constructor
    m_gameObjects.push_back(_gameObject);
}

void Scene::RemoveGameObject(GameObject* _gameObject)
{
    bool removed = false;
    for (size_t i = 0; i < m_gameObjects.size(); i++)
    {
        if (m_gameObjects[i] == _gameObject)
        {
            removed = true;
        }
        if (removed)
        {
            m_gameObjects[i]->SetId(i - 1);
        }
    }
    std::erase(m_gameObjects, _gameObject);
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

bool Scene::IsNameExists(const std::string& _name)
{
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        if (m_gameObjects[i]->name == _name)
            return true;
    }
    return false;

}

void Scene::CreateNewObject(std::string _name, std::string _modelName, std::string _textureName, std::string _shaderName)
{
    ResourceManager* resourceManager = ResourceManager::GetInstance();

    std::string name = _name;
    Transform* transform = new Transform(Vector3(0), Vector3(0), Vector3(1), m_world->transform);

    Texture* texture;
    Shader* shader;

    if (_textureName.empty())
    {
        texture = resourceManager->Get<Texture>(SceneManager::m_defaultTexture);
    }
    else
    {
        texture = resourceManager->Get<Texture>(_textureName);
    }

    if (_shaderName.empty())
        shader = resourceManager->Get<Shader>(SceneManager::m_defaultShader); // Get default shader
    else
        shader = resourceManager->Get<Shader>(_shaderName);

    // Using the rename functions
    int suffix = 2;    // start at 2 because of two objects having the same name
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
        Model* model = resourceManager->Get<Model>(SceneManager::m_defaultModel);
        loadingObject = GetFileName(_filePath);
    }
    else
    {
        Model* model = resourceManager->Get<Model>(_resourceName);
        loadingObject = GetFileName(_filePath);
    }
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

const std::vector<GameObject*>& Scene::GetGameObjects()
{
    return m_gameObjects;
}

GameObject* Scene::GetWorld()
{
    return m_world;
}
