#include "WorldBuilder/worldBuilder.h"

#include "Resource/tools.h"
#include "Wrappers/graphicWrapper.h"


void WorldBuilder::Init()
{
    m_terrain = new Terrain(Tools::FindFile("heightmap.png").c_str());
    m_terrain->GenerateVertexData(0.4f);
    m_terrain->GenerateIndexData();
}

void WorldBuilder::RenderTerrainData()
{
    glGenVertexArrays(1, &m_terrain->vao);
    glGenBuffers(1, &m_terrain->vbo);
    glGenBuffers(1, &m_terrain->ebo);

    glBindVertexArray(m_terrain->vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_terrain->vbo);
    glBufferData(GL_ARRAY_BUFFER, m_terrain->vertices.size() * sizeof(TerrainVertex), m_terrain->vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_terrain->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_terrain->indices.size() * sizeof(int), m_terrain->indices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TerrainVertex), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    std::cout << "highest y : " << m_terrain->highestPoint << "/nlowest y : " << m_terrain->lowestPoint << std::endl;
}

void WorldBuilder::RenderTerrain()
{
    glBindVertexArray(m_terrain->vao);
    glDrawElements(GL_TRIANGLES, (m_terrain->rows - 1) * (m_terrain->columns -1) * 6, GL_UNSIGNED_INT, 0);
}


Terrain* WorldBuilder::GetTerrain()
{
    return m_terrain;
}
