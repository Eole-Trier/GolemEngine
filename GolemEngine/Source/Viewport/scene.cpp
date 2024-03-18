#include "Viewport/scene.h"

#include "utils.h"
#include "Resource/resourceManager.h"
#include "Resource/Rendering/mesh.h"
#include "Resource/Rendering/model.h"
#include "Resource/Rendering/texture.h"
#include "Resource/Rendering/shader.h"
#include "Resource/tools.h"
#include "Components/Light/point.h"
#include "Components/Light/directional.h"
#include "Components/Light/spot.h"
#include "Resource/Rendering/shader.h"
#include "Core/gameobject.h"
#include "Core/transform.h"

Scene::Scene() 
{
    m_world = nullptr;
}

void Scene::Init()
{
    CreateAndLoadResources();
    InitLights();
    InitGameObjects();
}

void Scene::InitGameObjects()
{
    ResourceManager* resourceManager = ResourceManager::GetInstance();
    m_world = new GameObject("World", new Transform(Vector3(0, 0, 0), Vector3(0), Vector3(1)));

    Shader* defaultShader = resourceManager->Get<Shader>("default");

    std::string vikingName = "viking";
    Transform* vikingTransform = new Transform(Vector3(0), Vector3(0), Vector3(1));
    Texture* viking_text = resourceManager->Get<Texture>("viking_texture");
    Model* viking_room = resourceManager->Get<Model>("model_viking");

    std::string ballBaldName = "ball_bald";
    Transform* ballBaldTransform = new Transform(Vector3(3, 0, 0), Vector3(0), Vector3(1));
    Texture* ballBaldTexture = resourceManager->Get<Texture>("all_bald_texture");
    Model* ballBald = resourceManager->Get<Model>("model_sphere");

    Mesh* vikingMesh = new Mesh(vikingName, vikingTransform, viking_room, viking_text, defaultShader);
    Mesh* ballBaldMesh = new Mesh(ballBaldName, ballBaldTransform, ballBald, ballBaldTexture, defaultShader);

    m_meshes.push_back(vikingMesh);
    m_meshes.push_back(ballBaldMesh);

    m_gameObjects.push_back(vikingMesh);
    m_gameObjects.push_back(ballBaldMesh);

    m_world->transform->AddChild(vikingMesh->transform);
    vikingMesh->transform->AddChild(ballBaldMesh->transform);
}

void Scene::Update(float _width, float _height, GLFWwindow* _window, Camera* _camera)
{
    ResourceManager* resourceManager = ResourceManager::GetInstance();
    Shader* viking = resourceManager->Get<Shader>("default");
    viking->Use();

    viking->SetViewPos(_camera->m_position);

    UpdateLights(viking);
    UpdateGameObjects(_width, _height, _window, _camera);
}

void Scene::UpdateGameObjects(float _width, float _height, GLFWwindow* _window, Camera* _camera)
{
    // Temporary to test graph scene
    m_meshes[0]->transform->rotation.y += 0.01f;
    m_meshes[1]->transform->rotation.x += 0.01f;
    m_world->transform->UpdateSelfAndChilds();
    for (int i = 0; i < m_meshes.size(); i++)
    {
        m_meshes[i]->Draw(_width, _height, _camera);
    }
}

void Scene::InitLights()
{
    // Set up the sun
    m_dirLights.push_back(new DirectionalLight(Vector4(0.4f, 0.4f, 0.4f, 0.4f), Vector4(0.05f, 0.05f, 0.05f, 0.05f), Vector4(0.5f, 0.5f, 0.5f, 0.5f),
        Vector3(-0.2f, -1.0f, -0.3f), m_dirLights, m_maxDirLights));

    // Add some point lights
    m_pointLights.push_back(new PointLight(Vector4(1.f, 1.f, 1.f, 1.f), Vector4(1.f, 1.f, 1.f, 1.f), Vector4(1.f, 1.f, 1.f, 1.f),
        Vector3(3, 0, 0), 1.f, 2.f, 1.f, m_pointLights, m_maxPointLights));
    m_pointLights.push_back(new PointLight(Vector4(0.8f, 0.8f, 0.8f, 0.8f), Vector4(0.05f, 0.05f, 0.05f, 0.05f), Vector4(1.0f, 1.0f, 1.0f, 1.f),
        Vector3(0, 0, 2), 1.0f, 0.09f, 0.032f, m_pointLights, m_maxPointLights));
}

void Scene::CreateAndLoadResources()
{
    ResourceManager* resourceManager = ResourceManager::GetInstance();
    Texture* text = resourceManager->Create<Texture>("viking_texture");
    text->Load(Tools::FindFile("viking_room.jpg").c_str());

    Model* viking_room = resourceManager->Create<Model>("model_viking");
    viking_room->Load(Tools::FindFile("viking_room.obj").c_str());

    Shader* shad = resourceManager->Create<Shader>("default");
    shad->SetVertexAndFragmentShader("Shaders/default.vs", "Shaders/default.fs");


    Texture* sphere_texture = resourceManager->Create<Texture>("all_bald_texture");
    sphere_texture->Load("Assets/One_For_All/Textures/all_bald.jpg");

    Model* sphere = resourceManager->Create<Model>("model_sphere");
    sphere->Load("Assets/Basics/sphere.obj");
}

void Scene::UpdateLights(Shader* _shader)
{
    _shader->Use();

    _shader->SetInt("nbrDirectionalLights", m_dirLights.size());
    for (unsigned int i = 0; i < m_dirLights.size(); ++i)
    {
        m_dirLights[i]->SetDirectionalLight(_shader);
    }
    _shader->SetInt("nbrPointLights", m_pointLights.size());
    for (unsigned int i = 0; i < m_pointLights.size(); ++i)
    {
        m_pointLights[i]->SetPointLight(_shader);
    }

    _shader->SetInt("nbrSpotLights", m_spotLights.size());
    for (unsigned int i = 0; i < m_spotLights.size(); ++i)
    {
        m_spotLights[i]->SetSpotLight(_shader);
    }
}

Mesh* Scene::GetMeshByName(std::string _name)
{
    for (Mesh* mesh : m_meshes)
    {
        if (mesh->GetName() == _name)
            return mesh;
    }
    Log::Print("No mesh with the name %s has been found", _name.c_str());
    return nullptr;
}

const std::vector<GameObject*>& Scene::GetGameObjects()
{
    return m_gameObjects;
}

GameObject* Scene::GetWorld()
{
    return m_world;
}
