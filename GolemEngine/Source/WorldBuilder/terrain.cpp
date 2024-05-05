#include "WorldBuilder/terrain.h"

#include <utils.h>

#include "Wrappers/graphicWrapper.h"
#include "Resource/resourceManager.h"
#include "Resource/sceneManager.h"
#include "Wrappers/windowWrapper.h"
#include "Utils/viewportTools.h"
#include "Resource/Rendering/Shader/shader.h"


Terrain::Terrain(std::string _name, Transform* _transform)
    : GameObject(_name, _transform)
{}

Terrain::~Terrain()
{
    SceneManager::GetCurrentScene()->RemoveTerrain(this);
    DeleteAllComponents();
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

    glBindVertexArray(0);

    // Setup the compute shader
    glGenBuffers(1, &m_ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_ssbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_ssbo);
    
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void Terrain::UseComputeShader()
{
    m_computeShader->Use();
    glDispatchCompute(10, 10, 1);
    
    glMemoryBarrier(GL_ALL_BARRIER_BITS);
}

void Terrain::Draw(Camera* _camera)
{
    m_shader->Use();
    m_shader->GetVertexShader()->SetMat4("model", transform->GetGlobalModel());
    m_shader->GetVertexShader()->SetMat4("view", _camera->GetViewMatrix());
    m_shader->GetVertexShader()->SetMat4("projection", Matrix4::Projection(DegToRad(_camera->GetZoom()), WindowWrapper::GetScreenSize().x / WindowWrapper::GetScreenSize().y, _camera->GetNear(), _camera->GetFar()));
    m_shader->GetVertexShader()->SetFloat("minHeight", m_yMin);
    std::cout << m_yMin << std::endl;
    m_shader->GetVertexShader()->SetFloat("maxHeight", m_yMax);
    
    glBindVertexArray(m_vao);
    
    // Switch draw mode depending on view mode
    switch (ViewportTools::currentViewMode)
    {
    case DEFAULT:
        glDrawElements(GL_TRIANGLES, (m_xResolution - 1) * (m_zResolution - 1) * 6, GL_UNSIGNED_INT, 0);
        break;

    case WIREFRAME:
        glDrawElements(GL_LINES, (m_xResolution - 1) * (m_zResolution - 1) * 6, GL_UNSIGNED_INT, 0);
        break;
    }
}

void Terrain::GetComputeShaderData(Camera* _camera)
{
    // Bind the SSBO containing the vertex data
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_ssbo);

    // Map the buffer to CPU memory
    void* ptr = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);

    if (ptr != nullptr)
    {
        // Copy the data to a CPU-accessible buffer
        Vertex* verticesData = static_cast<Vertex*>(ptr);
        std::vector<Vertex> cpuBuffer(m_vertices.size()); // Assuming vertexCount is the total number of vertices

        // Get the model matrix to use them for calculation after
        Matrix4 modelMatrix = transform->GetGlobalModel();

        int batchSize = 100; // You can adjust this value based on performance testing

        float yMin = 0.0f;
        float yMax = 0.0f;
        
        for (int i = 0; i < m_vertices.size(); ++i)
        {
            // Get the original vertex position
            Vector4 originalPosition = Vector4(verticesData[i].position.x, verticesData[i].position.y, verticesData[i].position.z, 1.0f); // Assuming the position is in vec3 format
            // Apply the concatenated transformation matrix
            Vector4 transformedPosition = modelMatrix * originalPosition;
            // Perform perspective division
            Vector3 finalPosition = Vector3(transformedPosition.x, transformedPosition.y, transformedPosition.z);

            // Update the vertex position in the CPU buffer
            cpuBuffer[i].position = {finalPosition.x, finalPosition.y, finalPosition.z};

            if (finalPosition.y <= yMin)    // Store lowest vertex
            {
                yMin = finalPosition.y;
            }
            
            if (finalPosition.y >= yMax)    // Store highestPosition
            {
                yMax = finalPosition.y;
            }
        }
        m_yMin = yMin;
        m_yMax = yMax;
        // Unmap the buffer
        glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
    }
    else
    {
        std::cout << "vertex ptr is null" << std::endl;
    }

    // Don't forget to unbind the buffer after use
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

size_t Terrain::GetId()
{
    return m_id;
}
