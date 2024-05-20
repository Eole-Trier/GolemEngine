#include <string>
#include "Components/GameClasses/bullet.h"
#include "Components/GameClasses/movement.h"
#include "Components/meshRenderer.h"
#include "Components/component.h"
#include "Components/Physic/sphereCollider.h"
#include "Core/mesh.h"
#include "Core/gameobject.h"
#include "Resource/sceneManager.h"
#include "Resource/resourceManager.h"
#include "golemEngine.h"
#include "vector3.h"

Bullet::Bullet(Vector3 _initPosition, float _force, float _radius, Vector3 _direction, std::string _modelName, std::string _name, std::string _textureName, std::string _shaderName)
    : lifetime(0.0f),
    name(_name)
{
    ResourceManager* resourceManager = ResourceManager::GetInstance();

    m_transform = new Transform(_initPosition, Vector3(0), Vector3(_radius), SceneManager::GetCurrentScene()->GetWorld()->transform);

    if (_textureName.empty())
        texture = resourceManager->Get<Texture>(ResourceManager::GetDefaultTexture());
    else
        texture = resourceManager->Get<Texture>(_textureName);

    if (_shaderName.empty())
        shader = resourceManager->Get<Shader>(ResourceManager::GetDefaultShader());
    else
        shader = resourceManager->Get<Shader>(_shaderName);

    // Using the rename functions
    int suffix = 2; // start at 2 because of two objects having the same name
    std::string originalName = name;
    while (SceneManager::GetCurrentScene()->IsNameExists(name))
    {
        name = originalName + "_" + std::to_string(suffix++);
    }

    model = resourceManager->Get<Model>("sphere.obj");
    mesh = new Mesh(model, texture, shader);

    GameObject* gameObject = new GameObject(name, m_transform);
    gameObject->AddComponent(new MeshRenderer(mesh));
    //SceneManager::GetCurrentScene()->gameObjects.push_back(gameObject);
 
    //gameObject->AddComponent(new SphereCollider);

    forward = _direction;
    speed = 0.1f;
    isDead = false;
}

void Bullet::Update()
{

    if (lifetime > maxLifetime)
    {
        Destroy();
    }
    m_transform->localPosition += forward * speed;
    lifetime += GolemEngine::GetDeltaTime();
}

void Bullet::Destroy()
{
    isDead = true;
    //delete this;
}
