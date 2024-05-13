#include "WorldBuilder/noisemapTerrain.h"

#include "Resource/resourceManager.h"
#include "Image/stb_image.h"


NoisemapTerrain::NoisemapTerrain(std::string _name, Transform* _transform)
    : Terrain(_name, _transform)
{}

void NoisemapTerrain::Init(const char* _noisemapPath)
{
    m_noisemapPath = _noisemapPath;
    
    // Set shader
    ResourceManager* resourceManager = ResourceManager::GetInstance();
    m_shader = resourceManager->Get<Shader>(ResourceManager::GetDefaultTerrainShader());
    m_computeShader = resourceManager->Get<ComputeShader>(ResourceManager::GetDefaultTerrainComputeShader());

    // Load noisemap
    stbi_set_flip_vertically_on_load(false);
    unsigned char* noisemap = stbi_load(_noisemapPath, &xResolution, &zResolution, &m_nChannel, STBI_grey);
    std::vector<int> noisemapValues;
    
    for (int i = 0; i < xResolution; i++)
    {
        for (int j = 0; j < zResolution; j++)
        {
            unsigned int noisemapValue = (noisemap + (i + xResolution * j))[0];
            // Set the vertex position
            Vertex vertex;
            vertex.position.x =(i / (float)xResolution) - 0.5f;    // - 0.5f to center to center origin
            vertex.position.z =(j / (float)zResolution) - 0.5f;    // - 0.5f to center to center origin
            vertex.position.y = noisemapValue / 255.0f;

            // Set highest vertex for the shader
            if(vertex.position.y > m_yMax)
            {
                m_yMax = vertex.position.y;
            }
            
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

std::string NoisemapTerrain::GetNoisemapPath()
{
    return m_noisemapPath;
}

void NoisemapTerrain::SetNoisemapPath(std::string _noisemapPath)
{
    m_noisemapPath = _noisemapPath;
}
