#include <string>
#include "Components/GameClasses/bullet.h"
#include "Components/GameClasses/movement.h"
#include "Components/meshRenderer.h"
#include "Components/component.h"
#include "Core/mesh.h"
#include "Core/gameobject.h"
#include "Resource/sceneManager.h"
#include "Resource/resourceManager.h"
#include "golemEngine.h"
#include "vector3.h"

Bullet::Bullet(std::string _modelName, std::string _name, std::string _textureName, std::string _shaderName)
{
    ResourceManager* resourceManager = ResourceManager::GetInstance();

    std::string name = _name;
    m_transform = new Transform(Vector3(0), Vector3(0), Vector3(1), SceneManager::GetCurrentScene()->GetWorld()->transform);
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
    while (SceneManager::GetCurrentScene()->IsNameExists(name))    // If an object already has the same name, add "_[suffix]" to it to make new name
    {
        name = originalName + "_" + std::to_string(suffix++);
    }

    Model* model = resourceManager->Get<Model>("sphere.obj");
    Mesh* mesh = new Mesh(model, texture, shader);
    GameObject* gameObject = new GameObject(name, m_transform);
    gameObject->AddComponent(new MeshRenderer(mesh));
    SceneManager::GetCurrentScene()->gameObjects.push_back(gameObject);
}

void Bullet::Update()
{
    m_transform->localPosition.z -= 0.1f;
    GolemEngine::GetDeltaTime();
}