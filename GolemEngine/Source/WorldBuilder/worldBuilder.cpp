#include "WorldBuilder/worldBuilder.h"

#include "Resource/sceneManager.h"
#include "WorldBuilder/defaultTerrain.h"
#include "WorldBuilder/noisemapTerrain.h"


void WorldBuilder::Init()
{
    
}

void WorldBuilder::CreateDefaultTerrain(int _xResolution, int _zResolution)
{
    std::string name = "Default Terrain";
    Transform* transform = new Transform();
    DefaultTerrain* terrain = new DefaultTerrain(name, transform);
    SceneManager::GetCurrentScene()->AddTerrain(terrain);
    terrain->Init(_xResolution, _zResolution);
}

void WorldBuilder::CreateNoisemapTerrain(const char* _noisemapPath)
{
    std::string name = "Noisemap Terrain";
    Transform* transform = new Transform();
    NoisemapTerrain* terrain = new NoisemapTerrain(name, transform);
    SceneManager::GetCurrentScene()->AddTerrain(terrain);
    terrain->Init(_noisemapPath);
}

