#pragma once 
#include "dll.h"]
#include "Core/scene.h"
#include "Core/gameobject.h"
#include "Resource/sceneManager.h"
#include "Resource/resourceManager.h"
#include "Components/meshRenderer.h"
#include "Components/component.h"
#include "Components/Physic/sphereCollider.h"
#include "Core/mesh.h"
#include "vector3.h"
#include <string>

class GOLEM_ENGINE_API Bullet : public GameObject
{
private:
	SphereCollider* m_sphereCollider;
public:
	Texture* texture;
	Shader* shader;
	Model* model;
	Mesh* mesh;

	Vector3 forward;


	Bullet(Vector3 _initPosition, float _lifeTime, float _radius, Vector3 _direction, std::string _modelName = "", std::string _name = "bullet", std::string _textureName = "", std::string _shaderName = "");

	void Update() override;

	void FunctionThatIGiveToACollider(Collider* _collider, Collider* _other);

	float speed;
	float lifetime;
};