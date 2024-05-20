#include "WorldBuilder/defaultTerrain.h"

#include "Resource/resourceManager.h"


DefaultTerrain::DefaultTerrain(std::string _name, Transform* _transform)
    : Terrain(_name, _transform)
{}

void DefaultTerrain::Init(int _xResolution, int _zResolution)
{
    xResolution = _xResolution;
    zResolution = _zResolution;
    
    // Make a grid of vertices using the terrain's dimensions
    for (int i = 0; i < xResolution; i++)
    {
        for (int j = 0; j < zResolution; j++)
        {
            // Set the vertex position
            VertexGpu vertex;
            vertex.position.x = (i / (float)xResolution) - 0.5f;    // - 0.5f to center to center origin
            vertex.position.z = (j / (float)zResolution) - 0.5f;    // - 0.5f to center to center origin
            vertex.position.y = 0.0f;
            // Set the vertex texture postion
            vertex.textureCoords.x = (j / (float)zResolution);
            vertex.textureCoords.y = 1.0f - (i / (float)xResolution);
            
            m_vertices.push_back(vertex);
        }
    }
    m_vertices[4].position.y = 0.3f;
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
