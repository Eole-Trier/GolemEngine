#include "WorldBuilder/worldBuilder.h"

#include <iostream>

#include "Resource/sceneManager.h"


void WorldBuilder::Init()
{
    
}

void WorldBuilder::CreateTerrain(int _xSize, int _zSize)
{
    SceneManager::GetCurrentScene()->AddTerrain(new Terrain(_xSize, _zSize));
}

