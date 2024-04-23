#include "WorldBuilder/worldBuilder.h"

#include "Resource/sceneManager.h"
#include "WorldBuilder/defaultTerrain.h"
#include "WorldBuilder/noisemapTerrain.h"


void WorldBuilder::Init()
{
    
}

void WorldBuilder::CreateDefaultTerrain(int _xResolution, int _zResolution, Vector2 _size)
{
    DefaultTerrain* terrain = new DefaultTerrain();
    SceneManager::GetCurrentScene()->AddTerrain(terrain);
    terrain->Init(_xResolution, _zResolution, _size);
}

void WorldBuilder::CreateNoisemapTerrain(const char* _noisemapPath, Vector2 _size, float _amplitude)
{
    NoisemapTerrain* terrain = new NoisemapTerrain();
    SceneManager::GetCurrentScene()->AddTerrain(terrain);
    terrain->Init(_noisemapPath, _size, _amplitude);
}

