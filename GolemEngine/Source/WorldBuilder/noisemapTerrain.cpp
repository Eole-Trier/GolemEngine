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

    // Load noisemap
    stbi_set_flip_vertically_on_load(false);
    unsigned char* noisemap = stbi_load(_noisemapPath, &m_xResolution, &m_zResolution, &m_nChannel, STBI_grey);
    std::vector<int> noisemapValues;
    
    for (int i = 0; i < m_xResolution; i++)
    {
        for (int j = 0; j < m_zResolution; j++)
        {
            unsigned int noisemapValue = (noisemap + (i + m_xResolution * j))[0];
            // Set the vertex position
            Vertex vertex;
            vertex.position.x =(i / (float)m_xResolution) - 0.5f;    // - 0.5f to center to center origin
            vertex.position.z =(j / (float)m_zResolution) - 0.5f;    // - 0.5f to center to center origin
            vertex.position.y = noisemapValue / 255.0f;

            // Set highest vertex for the shader
            if(vertex.position.y > m_yMax)
            {
                m_yMax = vertex.position.y;
            }
            
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

std::string NoisemapTerrain::GetNoisemapPath()
{
    return m_noisemapPath;
}

void NoisemapTerrain::SetNoisemapPath(std::string _noisemapPath)
{
    m_noisemapPath = _noisemapPath;
}
