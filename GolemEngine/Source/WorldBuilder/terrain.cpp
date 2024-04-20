#include "WorldBuilder/terrain.h"

#include "Wrappers/graphicWrapper.h"


Terrain::Terrain(int _xResolution, int _zResolution, float _generationScale)
    : xResolution(_xResolution), zResolution(_zResolution)
{
    // Make a grid of vertices using the terrain's dimensions
    for (int i = 0; i < xResolution; i++)
    {
        for (int j = 0; j < zResolution; j++)
        {
            // Set the vertex position
            Vertex vertex;
            // vertex.position.x = i;
            // vertex.position.z = j;
            vertex.position.x = (i / (float)xResolution) * _generationScale;
            vertex.position.z = -10 + (j / (float)zResolution) * _generationScale;    // -10 for offset but remove later
            vertex.position.y = 0.0f;
            // Set the vertex texture postion
            vertex.textureCoords.x = (j / (float)zResolution);
            vertex.textureCoords.y = 1.0f - (i / (float)xResolution);
            
            m_vertices.push_back(vertex);
        }
    }
    // Setup indices
    for (int i = 0; i < xResolution; i++)
    {
        for (int j = 0; j < zResolution - 1; j++)    // - 1 because of range error
        {
            m_indices.push_back(i * zResolution + j);
            m_indices.push_back((i + 1) * zResolution + j);
            m_indices.push_back(i * zResolution + j + 1);

            m_indices.push_back(i * zResolution + j + 1);
            m_indices.push_back((i + 1) * zResolution + j);
            m_indices.push_back((i + 1) * zResolution + j + 1);
        }
    }

    SetupMesh();
}

void Terrain::SetupMesh()
{
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);
    // Bindings
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
    glDrawElements(GL_TRIANGLES, (xResolution - 1) * (zResolution - 1) * 6, GL_UNSIGNED_INT, 0);
}
