#include "Components/GameClasses/shot.h"
#include "Components/GameClasses/bullet.h"
#include "Inputs/inputManager.h"
#include "Resource/sceneManager.h"
#include "golemEngine.h"
#include <iostream>

Shot::Shot()
{
	// Set bullet

}

Shot::~Shot()
{
    for (auto b : bullets)
    {
        delete b;
    }
    bullets.clear();
}

void Shot::Update()
{
	if (InputManager::IsKeyPressed(KEY_SPACE))
	{
		instantiate();
	}

    for (auto b : bullets)
    {
		if (b->isDead)
		{
			SceneManager::GetCurrentScene()->gameObjects.erase(std::remove(SceneManager::GetCurrentScene()->gameObjects.begin(), SceneManager::GetCurrentScene()->gameObjects.end(), b->b_ptr), SceneManager::GetCurrentScene()->gameObjects.end());
		}
		b->Update();
    }
	// TODO
	//for (auto it = bullets.begin(); it != bullets.end();)
	//{
	//	Bullet* b = *it;
	//	b->Update();
	//	if (b->isDead)
	//	{
	//		SceneManager::GetCurrentScene()->gameObjects.erase(std::remove(SceneManager::GetCurrentScene()->gameObjects.begin(), SceneManager::GetCurrentScene()->gameObjects.end(), b->b_ptr), SceneManager::GetCurrentScene()->gameObjects.end());
	//		delete b;
	//		it = bullets.erase(it);
	//	}
	//	else
	//	{
	//		++it;
	//	}
	//}
}

void Shot::instantiate()
{
	// Instantiate a bullet
	std::cout << "Shot !!" << std::endl;

    Bullet *bullet = new Bullet(owner->transform->localPosition, 0, radius, owner->transform->GetForward());
	bullets.push_back(bullet);
}