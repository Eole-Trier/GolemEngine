#include "WorldBuilder/worldBuilder.h"

#include "Resource/sceneManager.h"
#include "WorldBuilder/defaultTerrain.h"
#include "WorldBuilder/noisemapTerrain.h"
#include "Resource/sceneManager.h"


void WorldBuilder::Init()
{
    
}

void WorldBuilder::CreateDefaultTerrain(int _xResolution, int _zResolution)
{
    // For name creation to not have double names
    int suffix = 2;
    std::string name = "Default_Terrain";
    std::string originalName = name;
    while (SceneManager::GetCurrentScene()->IsNameExists(name))
    {
        name = originalName + "_" + std::to_string(suffix++);
    }
    
    Transform* transform = new Transform();
    DefaultTerrain* terrain = new DefaultTerrain(name, transform);
    SceneManager::GetCurrentScene()->AddTerrain(terrain);
    terrain->Init(_xResolution, _zResolution);
}

void WorldBuilder::CreateNoisemapTerrain(const char* _noisemapPath)
{
    // For name creation to not have double names
    int suffix = 2;
    std::string name = "Noisemap_Terrain";
    std::string originalName = name;
    while (SceneManager::GetCurrentScene()->IsNameExists(name))
    {
        name = originalName + "_" + std::to_string(suffix++);
    }
    
    Transform* transform = new Transform();
    NoisemapTerrain* terrain = new NoisemapTerrain(name, transform);
    SceneManager::GetCurrentScene()->AddTerrain(terrain);
    terrain->Init(_noisemapPath);
}

