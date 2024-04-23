#include "WorldBuilder/defaultTerrain.h"

#include "Resource/resourceManager.h"


DefaultTerrain::DefaultTerrain() {}

void DefaultTerrain::Init(int _xResolution, int _zResolution, Vector2 _size)
{
    p_xResolution = _xResolution;
    p_zResolution = _zResolution;
    p_size = _size;
    
    // Set shader
    ResourceManager* resourceManager = ResourceManager::GetInstance();
    p_shader = resourceManager->Get<Shader>(ResourceManager::GetDefaultTerrainShader());
    
    // Make a grid of vertices using the terrain's dimensions
    for (int i = 0; i < p_xResolution; i++)
    {
        for (int j = 0; j < p_zResolution; j++)
        {
            // Set the vertex position
            Vertex vertex;
            vertex.position.x = (i / (float)p_xResolution) * _size.x;
            vertex.position.z = -10 + (j / (float)p_zResolution) * _size.y;    // -10 for offset but remove later
            vertex.position.y = 0.0f;
            // Set the vertex texture postion
            vertex.textureCoords.x = (j / (float)p_zResolution);
            vertex.textureCoords.y = 1.0f - (i / (float)p_xResolution);
            
            p_vertices.push_back(vertex);
        }
    }
    // Setup indices
    for (int i = 0; i < p_xResolution; i++)
    {
        for (int j = 0; j < p_zResolution - 1; j++)    // - 1 because of range error
        {
            p_indices.push_back(i * p_zResolution + j);
            p_indices.push_back((i + 1) * p_zResolution + j);
            p_indices.push_back(i * p_zResolution + j + 1);

            p_indices.push_back(i * p_zResolution + j + 1);
            p_indices.push_back((i + 1) * p_zResolution + j);
            p_indices.push_back((i + 1) * p_zResolution + j + 1);
        }
    }

    SetupMesh();
}
