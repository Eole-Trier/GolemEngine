#include "WorldBuilder/worldBuilder.h"

#include "Resource/sceneManager.h"
#include "WorldBuilder/defaultTerrain.h"
#include "WorldBuilder/noisemapTerrain.h"


void WorldBuilder::Init()
{
    
}

void WorldBuilder::CreateDefaultTerrain(int _xResolution, int _zResolution, Vector2 _size)
{
    std::string name = "Default Terrain";
    Transform* transform = new Transform();
    DefaultTerrain* terrain = new DefaultTerrain(name, transform);
    SceneManager::GetCurrentScene()->AddTerrain(terrain);
    terrain->Init(_xResolution, _zResolution, _size);
}

void WorldBuilder::CreateNoisemapTerrain(const char* _noisemapPath, Vector2 _size, float _amplitude)
{
    std::string name = "Noisemap Terrain";
    Transform* transform = new Transform();
    std::cout << transform->scaling << std::endl;
    NoisemapTerrain* terrain = new NoisemapTerrain(name, transform);
    SceneManager::GetCurrentScene()->AddTerrain(terrain);
    terrain->Init(_noisemapPath, _size, _amplitude);
}

