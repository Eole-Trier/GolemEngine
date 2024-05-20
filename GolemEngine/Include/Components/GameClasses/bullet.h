#pragma once 
#include "dll.h"
#include "Core/gameobject.h"
#include "Resource/resourceManager.h"

class GOLEM_ENGINE_API Bullet : public GameObject
{
private:
	ResourceManager* resourceManager = ResourceManager::GetInstance();
public:

	Bullet();
	~Bullet();
};