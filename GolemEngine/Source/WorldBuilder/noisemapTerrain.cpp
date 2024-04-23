#include "WorldBuilder/noisemapTerrain.h"

#include "Resource/resourceManager.h"
#include "Image/stb_image.h"


NoisemapTerrain::NoisemapTerrain() {}

void NoisemapTerrain::Init(const char* _noisemapPath, Vector2 _size, float _amplitude)
{
    m_noisemapPath = _noisemapPath;
    p_size = _size;
    m_amplitude = _amplitude;
    
    // Set shader
    ResourceManager* resourceManager = ResourceManager::GetInstance();
    p_shader = resourceManager->Get<Shader>(ResourceManager::GetDefaultTerrainShader());

    // Load noisemap
    stbi_set_flip_vertically_on_load(false);
    unsigned char* noisemap = stbi_load(_noisemapPath, &p_xResolution, &p_zResolution, &m_nChannel, STBI_grey);
    std::vector<int> noisemapValues;
    
    for (int i = 0; i < p_xResolution; i++)
    {
        for (int j = 0; j < p_zResolution; j++)
        {
            unsigned int noisemapValue = (noisemap + (i + p_xResolution * j))[0];
            // Set the vertex position
            Vertex vertex;
            vertex.position.x = (i / (float)p_xResolution) * _size.x;
            vertex.position.z = -10 + (j / (float)p_zResolution) * _size.y;    // -10 for offset but remove later
            vertex.position.y = noisemapValue / 255.0f * _amplitude;

            // Set highest vertex for the shader
            if(_amplitude > 0.0f && vertex.position.y > p_yMax)
            {
                p_yMax = vertex.position.y;
            }
            else if (_amplitude < 0.0f && vertex.position.y < p_yMax)    // Handle the case where the amplitude is negative
            {
                p_yMax = vertex.position.y;
                std::cout << p_yMax << std::endl;
            }
            
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

std::string NoisemapTerrain::GetNoisemapPath()
{
    return m_noisemapPath;
}

void NoisemapTerrain::SetNoisemapPath(std::string _noisemapPath)
{
    m_noisemapPath = _noisemapPath;
}
