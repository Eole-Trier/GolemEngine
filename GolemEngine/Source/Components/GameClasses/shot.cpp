#include "Components/GameClasses/shot.h"
#include "Components/GameClasses/bullet.h"
#include "Inputs/inputManager.h"
#include "Resource/sceneManager.h"
#include "golemEngine.h"
#include <iostream>

Shot::Shot()
{
	radius = 0.1f;
}

Shot::~Shot()
{
}

void Shot::Begin()
{
	currentInteval = interval;
}

void Shot::Update()
{
	currentInteval -= GolemEngine::GetDeltaTime();
	if (currentInteval <= 0)
	{
		if (InputManager::IsKeyPressed(KEY_SPACE))
		{
			instantiateBullet();
		}
	}
}

void Shot::instantiateBullet()
{
	std::string name = "bullet";
	// Using the rename functions
	int suffix = 2; // start at 2 because of two objects having the same name
	std::string originalName = name;
	while (SceneManager::GetCurrentScene()->IsNameExists(name))
	{
		name = originalName + "_" + std::to_string(suffix++);
	}

	Bullet* bullet = new Bullet(owner->transform->localPosition, bulletLifetime, radius, owner->transform->GetForward(),"", name);

	currentInteval = interval;
}
