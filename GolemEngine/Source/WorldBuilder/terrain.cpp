#include "WorldBuilder/terrain.h"

#include <utils.h>

#include "golemEngine.h"
#include "Image/stb_image.h"
#include "Wrappers/graphicWrapper.h"
#include "Resource/resourceManager.h"
#include "Resource/sceneManager.h"
#include "Wrappers/windowWrapper.h"


Terrain::Terrain(int _xResolution, int _zResolution, Vector2 _size)
    : m_xResolution(_xResolution), m_zResolution(_zResolution)
{
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

Terrain::Terrain(const char* _noisemapPath, Vector2 _size, float _amplitude)
{
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
            vertex.position.x = (i / (float)m_xResolution) * _size.x;
            vertex.position.z = -10 + (j / (float)m_zResolution) * _size.y;    // -10 for offset but remove later
            vertex.position.y = noisemapValue / 255.0f * _amplitude;

            // Set highest vertex for the shader
            if(_amplitude > 0.0f && vertex.position.y > m_yMax)
            {
                m_yMax = vertex.position.y;
            }
            else if (_amplitude < 0.0f && vertex.position.y < m_yMax)    // Handle the case where the amplitude is negative
            {
                m_yMax = vertex.position.y;
                std::cout << m_yMax << std::endl;
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

void Terrain::Draw(Camera* _camera)
{
    SetupMesh();
    m_shader->Use();
    m_shader->SetMat4("model", SceneManager::GetCurrentScene()->GetWorld()->transform->GetGlobalModel());
    m_shader->SetMat4("view", _camera->GetViewMatrix());
    m_shader->SetMat4("projection", Matrix4::Projection(DegToRad(_camera->GetZoom()), WindowWrapper::GetScreenSize().x / WindowWrapper::GetScreenSize().y, _camera->GetNear(), _camera->GetFar()));
    m_shader->SetFloat("maxHeight", m_yMax);
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, (m_xResolution - 1) * (m_zResolution - 1) * 6, GL_UNSIGNED_INT, 0);
}
