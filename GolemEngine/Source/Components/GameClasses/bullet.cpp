#include <string>
#include "Components/GameClasses/bullet.h"
#include "Components/GameClasses/movement.h"
#include "Components/meshRenderer.h"
#include "Components/component.h"
#include "Components/Physic/sphereCollider.h"
#include "Core/mesh.h"
#include "Core/scene.h"
#include "Core/gameobject.h"
#include "Resource/sceneManager.h"
#include "Resource/resourceManager.h"
#include "golemEngine.h"
#include "vector3.h"

Bullet::Bullet(Vector3 _initPosition, float _lifeTime, float _radius, Vector3 _direction, std::string _modelName, std::string _name, std::string _textureName, std::string _shaderName)
	: lifetime(_lifeTime),
	forward(_direction),
	speed(0.1f)
{
	this->name = _name;

	ResourceManager* resourceManager = ResourceManager::GetInstance();

	transform->localPosition = _initPosition;
	transform->rotation = 0;
	transform->scaling = _radius;
	//transform->SetParent(SceneManager::GetCurrentScene()->GetWorld()->transform);
	
	if (_textureName.empty())
	    texture = resourceManager->Get<Texture>(ResourceManager::GetDefaultTexture());
	else
	    texture = resourceManager->Get<Texture>(_textureName);
	
	if (_shaderName.empty())
	    shader = resourceManager->Get<Shader>(ResourceManager::GetDefaultShader());
	else
	    shader = resourceManager->Get<Shader>(_shaderName);
	
	model = resourceManager->Get<Model>("sphere.obj");
	mesh = new Mesh(model, texture, shader);
	
	this->AddComponent(new MeshRenderer(mesh));

	m_sphereCollider = new SphereCollider();
	AddComponent(m_sphereCollider);
	m_sphereCollider->Begin();
	m_sphereCollider->radius = _radius;
	m_sphereCollider->motionType = MotionType::Dynamic;
	m_sphereCollider->isActivated = true;
	m_sphereCollider->onCollisionEnter = [this](Collider* _collider, Collider* _other) -> void { FunctionThatIGiveToACollider(m_sphereCollider, _other); };
}

void Bullet::Update()
{
	transform->localPosition += forward * speed;

	lifetime -= GolemEngine::GetDeltaTime();
	if (lifetime < 0)
	{
		SceneManager::GetCurrentScene()->AddDeletedGameObject(this);
	}
}

void Bullet::FunctionThatIGiveToACollider(Collider* _collider, Collider* _other)
{
	SceneManager::GetCurrentScene()->AddDeletedGameObject(_other->owner);
}
