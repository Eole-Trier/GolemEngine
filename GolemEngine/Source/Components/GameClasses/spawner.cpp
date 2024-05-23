#include "Components/GameClasses/spawner.h"
#include "Core/scene.h"
#include "Core/gameobject.h"
#include "Resource/sceneManager.h"
#include "Resource/resourceManager.h"
#include "Components/meshRenderer.h"
#include "Components/component.h"
#include "Components/Physic/sphereCollider.h"
#include "Components/Physic/boxCollider.h"
#include "Components/GameClasses/enemy.h"
#include "Core/mesh.h"
#include "vector3.h"
#include <string>

#include "golemEngine.h"
Spawner::Spawner()
{
}

Spawner::~Spawner()
{
}

void Spawner::Begin()
{
}

void Spawner::Update()
{
	std::string name = "Enemy";
	// Using the rename functions
	int suffix = 2; // start at 2 because of two objects having the same name
	std::string originalName = name;
	while (SceneManager::GetCurrentScene()->IsNameExists(name))
	{
		name = originalName + "_" + std::to_string(suffix++);
	}

	if(GolemEngine::GetGameMode())
		interval -= GolemEngine::GetDeltaTime();

	if (interval <= 0)
	{
		Spawn(name);
		interval = spawnInterval;
	}
}

void Spawner::Spawn(const std::string& _name)
{
	//ResourceManager* resourceManager = ResourceManager::GetInstance();
	//Transform* transform = new Transform(owner->transform);
	//GameObject* gameObject = new GameObject(_name, transform);
	//Texture* texture;
	//Model* model;
	//Shader* shader;
	//Mesh* mesh;
	//texture = resourceManager->Get<Texture>(ResourceManager::GetDefaultTexture());
	//shader = resourceManager->Get<Shader>(ResourceManager::GetDefaultShader());
	//model = resourceManager->Get<Model>("sphere.obj");
	//mesh = new Mesh(model, texture, shader);
	//gameObject->AddComponent(new MeshRenderer(mesh));
	//BoxCollider* boxCollider = new BoxCollider();
	//gameObject->AddComponent(boxCollider);
	//boxCollider->Begin();
	//boxCollider->motionType = MotionType::Dynamic;
	//boxCollider->isActivated = true;
	//boxCollider->gravityFactor = 0;
	Enemy* enemy = new Enemy(owner->transform->localPosition, _name);
}
