#pragma once 
#include "dll.h"
#include "Core/gameobject.h"
#include "Resource/resourceManager.h"
#include "vector3.h"
#include <string>

class GOLEM_ENGINE_API Bullet : public GameObject
{
private:
	Transform* m_transform;
public:

	Bullet(std::string _modelName = "", std::string _name = "bullet", std::string _textureName = "", std::string _shaderName = "");

	Bullet(Vector3 _initPosition, float _force, float _radius, Vector3 _direction);

	void Update();
};