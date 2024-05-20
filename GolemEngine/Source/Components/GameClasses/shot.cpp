#include "Components/GameClasses/shot.h"
#include "Components/GameClasses/bullet.h"
#include "Inputs/inputManager.h"
#include <iostream>

Shot::Shot()
{
	// Set bullet

}

Shot::~Shot()
{
}

void Shot::Update()
{
	if (InputManager::IsKeyPressed(KEY_SPACE))
	{
		instantiate();
	}

	for (auto &b : bullets)
	{
		b->Update();
	}
}

void Shot::instantiate()
{
	// Instantiate a bullet
	std::cout << "Shot !!" << std::endl;

	//Bullet bullet;

	bullets.push_back(new Bullet());
}
