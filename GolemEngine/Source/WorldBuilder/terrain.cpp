#include "WorldBuilder/terrain.h"

#include "Wrappers/graphicWrapper.h"


Terrain::Terrain(int _xSize, int _zSize)
    : xSize(_xSize), zSize(_zSize)
{
    // Make a grid of vertices using the terrain's dimensions
    for (int i = 0; i < xSize; i++)
    {
        for (int j = 0; j < zSize; j++)
        {
            // Set the vertex position
            Vertex vertex;
            vertex.position.x = i / xSize;
            vertex.position.z = i / zSize;
            // Set the vertex texture postion
            vertex.textureCoords.x = (1.0f / zSize * j);
            vertex.textureCoords.y = (1.0f - i / xSize);
            
            m_vertices.push_back(vertex);

            // Do indices
            m_indices.push_back((i - 1) * zSize + j - 1);
            m_indices.push_back((i - 1) * zSize + j);
            m_indices.push_back(i * zSize + j - 1);
            
            m_indices.push_back(i * zSize + j - 1);
            m_indices.push_back((i - 1) * zSize + j);
            m_indices.push_back(i * zSize + j);
        }
    }

    SetupMesh();
}

void Terrain::SetupMesh()
{
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(int), m_indices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Terrain::Draw()
{
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, (xSize - 1) * (zSize - 1) * 6, GL_UNSIGNED_INT, 0);
}
