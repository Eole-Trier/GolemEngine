#include "WorldBuilder/worldBuilder.h"

#include "Resource/tools.h"


void WorldBuilder::Init()
{
    m_terrain = new Terrain(Tools::FindFile("heigtmap.png").c_str());
    m_terrain->GenerateVertexData(0.4f);
    m_terrain->GenerateIndexData();
}

Terrain* WorldBuilder::GetTerrain()
{
    return m_terrain;
}
