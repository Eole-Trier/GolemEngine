#pragma once 
#include "dll.h"
#include "Core/gameobject.h"
#include "Resource/resourceManager.h"
#include "Components/meshRenderer.h"
#include "Components/component.h"
#include "Components/Physic/sphereCollider.h"
#include "Core/mesh.h"
#include "vector3.h"
#include <string>

class Bullet
{
private:
	Transform* m_transform;
public:
	std::string name;
	Texture* texture;
	Shader* shader;
	Model* model;
	Mesh* mesh;

	GameObject* b_ptr;

	GOLEM_ENGINE_API Bullet(Vector3 _initPosition, float _force, float _radius, Vector3 _direction, std::string _modelName = "", std::string _name = "bullet", std::string _textureName = "", std::string _shaderName = "");
	float speed;
	float lifetime;
	const float maxLifetime = 2.0f;

	bool isDead;
	
	Vector3 forward;

	GOLEM_ENGINE_API void Update();
	GOLEM_ENGINE_API void Destroy();
};