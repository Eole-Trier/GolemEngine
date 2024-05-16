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
{
    ResourceManager* resourceManager = ResourceManager::GetInstance();
    m_texture = resourceManager->Get<Texture>(ResourceManager::GetDefaultGridTerrainTexture());

    isTerrain = true;
}

Terrain::~Terrain()
{
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
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(VertexGpu), m_vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(int), m_indices.data(), GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexGpu), (void*)0);
    glEnableVertexAttribArray(0);
    // texture attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexGpu), (void*)offsetof(VertexGpu, textureCoords));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    // Setup the compute shader
    // Input buffer
    glGenBuffers(1, &m_ssboIn);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_ssboIn);
    glBufferData(GL_SHADER_STORAGE_BUFFER, m_vertices.size() * sizeof(VertexGpu), m_vertices.data(), GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_ssboIn);
    // Output buffer
    glGenBuffers(1, &m_ssboOut);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_ssboOut);
    glBufferData(GL_SHADER_STORAGE_BUFFER, m_vertices.size() * sizeof(VertexGpu), m_vertices.data(), GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, m_ssboOut);
    
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
    glActiveTexture(GL_TEXTURE0);
    m_texture->Use();

    m_shader->Use();
    m_shader->GetVertexShader()->SetMat4("model", transform->GetGlobalModel());
    m_shader->GetVertexShader()->SetMat4("view", _camera->GetViewMatrix());
    m_shader->GetVertexShader()->SetMat4("projection", Matrix4::Projection(DegToRad(_camera->GetZoom()), WindowWrapper::GetScreenSize().x / WindowWrapper::GetScreenSize().y, _camera->GetNear(), _camera->GetFar()));
    m_shader->GetVertexShader()->SetFloat("minHeight", m_yMin);
    m_shader->GetVertexShader()->SetFloat("maxHeight", m_yMax);
    m_shader->GetFragmentShader()->SetInt("ourTexture", 0);
    
    glBindVertexArray(m_vao);
    
    // Switch draw mode depending on view mode
    switch (ViewportTools::currentViewMode)
    {
    case DEFAULT:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        break;

    case WIREFRAME:
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        break;
    }
    
    glDrawElements(GL_TRIANGLES, (xResolution - 1) * (zResolution - 1) * 6, GL_UNSIGNED_INT, 0);
    // Reset to fill
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Terrain::GetComputeShaderData(Camera* _camera)
{
    // Bind the SSBO containing the vertex data
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_ssboOut);
    // Create a buffer to store the output of the gpu
    GLint bufferSize;
    glGetBufferParameteriv(GL_SHADER_STORAGE_BUFFER, GL_BUFFER_SIZE, &bufferSize);
    // Store the output to the buffer
    std::vector<VertexGpu> verticesOut(bufferSize / sizeof(VertexGpu));
    glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, bufferSize, verticesOut.data());
    
    if (!verticesOut.empty())
    {
        // Get the model matrix to use them for calculation after
        Matrix4 modelMatrix = transform->GetGlobalModel();

        float yMin = std::numeric_limits<float>::max();    // So that any value found in the loop HAS TO BE SMALLER than this
        float yMax = std::numeric_limits<float>::lowest();    // So that any value found in the loop HAS TO BE BIGGER than this

        if (m_oldModelMatrix != modelMatrix)
        {
            for (int i = 0; i < m_vertices.size(); ++i)
            {
                // Get the original vertex position
                Vector4 originalPosition = Vector4(verticesOut[i].position.x, verticesOut[i].position.y, verticesOut[i].position.z, 1.0f);
                // Apply the model matrix
                Vector4 transformedPosition = modelMatrix * originalPosition;
                // Set final position
                Vector3 finalPosition = Vector3(transformedPosition.x, transformedPosition.y, transformedPosition.z);
                // Update the vertex position in the CPU buffer
                m_vertices[i].position = finalPosition;
                // Set min and max point of the heightmap
                yMin = std::min(yMin, finalPosition.y);
                yMax = std::max(yMax, finalPosition.y);

                // m_vertices[i].normal = verticesOut[i].normal;
            }
            
            m_yMin = yMin;
            m_yMax = yMax;
        }

        m_oldModelMatrix = modelMatrix;

        glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
    }
    else
    {
        std::cout << "ERROR: vertex output from the compute shader is null" << std::endl;
    }

    // Don't forget to unbind the buffer after use
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void Terrain::CalculateNormals()
{
    for (int i = 0; i < xResolution; ++i)
    {
        for (int j = 0; j < zResolution; ++j)
        {
            Vector3 normal(0.0f, 0.0f, 0.0f);
            Vector3 currentPosition = m_vertices[j + i * zResolution].position;

            if (i < xResolution - 1 && j < zResolution - 1) // Bottom-right triangle
            {
                Vector3 bottomPosition = m_vertices[j + 1 + i * zResolution].position;
                Vector3 rightPosition = m_vertices[j + (i + 1) * zResolution].position;
                Vector3 bottom = bottomPosition - currentPosition;
                Vector3 right = rightPosition - currentPosition;
                normal += Vector3::Cross(bottom, right);
            }
            if (i < xResolution - 1 && j > 0) // Top-right triangle
            {
                Vector3 topPosition = m_vertices[j - 1 + i * zResolution].position;
                Vector3 rightPosition = m_vertices[j + (i + 1) * zResolution].position;
                Vector3 top = topPosition - currentPosition;
                Vector3 right = rightPosition - currentPosition;
                normal += Vector3::Cross(top, right);
            }
            if (i > 0 && j < zResolution - 1) // Bottom-left triangle
            {
                Vector3 bottomPosition = m_vertices[j + 1 + i * zResolution].position;
                Vector3 leftPosition = m_vertices[j + (i - 1) * zResolution].position;
                Vector3 bottom = bottomPosition - currentPosition;
                Vector3 left = leftPosition - currentPosition;
                normal += Vector3::Cross(bottom, left);
            }
            if (i > 0 && j > 0) // Top-left triangle
            {
                Vector3 topPosition = m_vertices[j - 1 + i * zResolution].position;
                Vector3 leftPosition = m_vertices[j + (i - 1) * zResolution].position;
                Vector3 top = topPosition - currentPosition;
                Vector3 left = leftPosition - currentPosition;
                normal += Vector3::Cross(left, top);
            }

            m_vertices[j + i * zResolution].normal = normal.Normalize();
        }
    }
}