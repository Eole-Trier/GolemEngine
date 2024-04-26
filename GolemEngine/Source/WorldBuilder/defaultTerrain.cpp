#include "WorldBuilder/defaultTerrain.h"

#include "Resource/resourceManager.h"


DefaultTerrain::DefaultTerrain() {}

void DefaultTerrain::Init(int _xResolution, int _zResolution, Vector2 _size)
{
    m_xResolution = _xResolution;
    m_zResolution = _zResolution;
    m_size = _size;
    
    // Set shader
    ResourceManager* resourceManager = ResourceManager::GetInstance();
    m_shader = resourceManager->Get<Shader>(ResourceManager::GetDefaultTerrainShader());
    
    // Make a grid of vertices using the terrain's dimensions
    for (int i = 0; i < m_xResolution; i++)
    {
        for (int j = 0; j < m_zResolution; j++)
        {
            // Set the vertex position
            Vertex vertex;
            vertex.position.x = (i / (float)m_xResolution) * _size.x;
            vertex.position.z = -10 + (j / (float)m_zResolution) * _size.y;    // -10 for offset but remove later
            vertex.position.y = 0.0f;
            // Set the vertex texture postion
            vertex.textureCoords.x = (j / (float)m_zResolution);
            vertex.textureCoords.y = 1.0f - (i / (float)m_xResolution);
            
            m_vertices.push_back(vertex);
        }
    }
    // Setup indices
    for (int i = 0; i < m_xResolution; i++)
    {
        for (int j = 0; j < m_zResolution - 1; j++)    // - 1 because of range error
        {
            m_indices.push_back(i * m_zResolution + j);
            m_indices.push_back((i + 1) * m_zResolution + j);
            m_indices.push_back(i * m_zResolution + j + 1);

            m_indices.push_back(i * m_zResolution + j + 1);
            m_indices.push_back((i + 1) * m_zResolution + j);
            m_indices.push_back((i + 1) * m_zResolution + j + 1);
        }
    }

    SetupMesh();
}
