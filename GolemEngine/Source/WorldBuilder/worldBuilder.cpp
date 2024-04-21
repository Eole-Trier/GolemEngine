#include "WorldBuilder/worldBuilder.h"

#include <iostream>

#include "Resource/sceneManager.h"


void WorldBuilder::Init()
{
    
}

void WorldBuilder::CreateTerrain(int _xResolution, int _zResolution, float _generationScale)
{
    SceneManager::GetCurrentScene()->AddTerrain(new Terrain(_xResolution, _zResolution, _generationScale));
}

void WorldBuilder::CreateTerrainNoisemap(const char* _noisemapPath, float _generationScale)
{
    SceneManager::GetCurrentScene()->AddTerrain(new Terrain(_noisemapPath, _generationScale));
}

