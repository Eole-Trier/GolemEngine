#include "WorldBuilder/terrain.h"

#include <utils.h>

#include "Image/stb_image.h"
#include "Wrappers/graphicWrapper.h"
#include "Resource/resourceManager.h"
#include "Resource/sceneManager.h"
#include "Wrappers/windowWrapper.h"


Terrain::Terrain(int _xResolution, int _zResolution, float _generationScale)
    : xResolution(_xResolution), zResolution(_zResolution)
{
    // Set shader
    ResourceManager* resourceManager = ResourceManager::GetInstance();
    m_shader = resourceManager->Get<Shader>(ResourceManager::GetDefaultTerrainShader());
    
    // Make a grid of vertices using the terrain's dimensions
    for (int i = 0; i < xResolution; i++)
    {
        for (int j = 0; j < zResolution; j++)
        {
            // Set the vertex position
            Vertex vertex;
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

Terrain::Terrain(const char* _noisemapPath, float _generationScale)
{
    // Set shader
    ResourceManager* resourceManager = ResourceManager::GetInstance();
    m_shader = resourceManager->Get<Shader>(ResourceManager::GetDefaultTerrainShader());

    // Load noisemap
    unsigned char* noisemap = stbi_load(_noisemapPath, &m_width, &m_height, &m_nChannel, STBI_grey);

    const int WIDTH = 204;
    const int HEIGHT = 205;
    const int WIDHT2 = 512;
    const int HEIGHT2 = 513;
    
    // Make a grid of vertices using the terrain's dimensions
    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            unsigned char noisemapValue = (noisemap + (i + WIDHT2 * j))[0];
            std::cout << noisemapValue << std::endl;
            Vertex vertex;
            vertex.position.x = i * 60.0f / WIDHT2;
            vertex.position.z = -10 + j * 60.0f / HEIGHT2;
            vertex.position.y = noisemapValue / 255.0f * 5;

            vertex.textureCoords.x = (1.0f / HEIGHT * j);
            vertex.textureCoords.y = (1 - i * 1.0f / WIDTH);
            
            m_vertices.push_back(vertex);
        }
    }
    // Setup indices
    for (int i = 0; i < m_width; i++)
    {
        for (int j = 0; j < m_height - 1; j++)    // - 1 because of range error
        {
            m_indices.push_back(i * m_height + j);
            m_indices.push_back((i + 1) * m_height + j);
            m_indices.push_back(i * m_height + j + 1);

            m_indices.push_back(i * m_height + j + 1);
            m_indices.push_back((i + 1) * m_height + j);
            m_indices.push_back((i + 1) * m_height + j + 1);
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
    m_shader->Use();
    m_shader->SetMat4("model", SceneManager::GetCurrentScene()->GetWorld()->transform->GetGlobalModel());
    m_shader->SetMat4("view", _camera->GetViewMatrix());
    m_shader->SetMat4("projection",  Matrix4::Projection(DegToRad(_camera->GetZoom()), WindowWrapper::GetScreenSize().x / WindowWrapper::GetScreenSize().y, _camera->GetNear(), _camera->GetFar()));
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, (xResolution - 1) * (zResolution - 1) * 6, GL_UNSIGNED_INT, 0);
}
