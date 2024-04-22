#include "WorldBuilder/worldBuilder.h"

#include "Resource/sceneManager.h"


void WorldBuilder::Init()
{
    
}

void WorldBuilder::CreateTerrain(int _xResolution, int _zResolution, Vector2 _size)
{
    SceneManager::GetCurrentScene()->AddTerrain(new Terrain(_xResolution, _zResolution, _size));
}

void WorldBuilder::CreateTerrainNoisemap(const char* _noisemapPath, Vector2 _size, float _amplitude)
{
    SceneManager::GetCurrentScene()->AddTerrain(new Terrain(_noisemapPath, _size, _amplitude));
}

