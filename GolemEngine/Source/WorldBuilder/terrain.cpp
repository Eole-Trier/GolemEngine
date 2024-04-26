#include "WorldBuilder/terrain.h"

#include <utils.h>

#include "Wrappers/graphicWrapper.h"
#include "Resource/resourceManager.h"
#include "Resource/sceneManager.h"
#include "Wrappers/windowWrapper.h"
#include "Utils/viewportTools.h"


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
    m_shader->SetMat4("projection", Matrix4::Projection(DegToRad(_camera->GetZoom()), WindowWrapper::GetScreenSize().x / WindowWrapper::GetScreenSize().y, _camera->GetNear(), _camera->GetFar()));
    m_shader->SetFloat("maxHeight", m_yMax);
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

size_t Terrain::GetId()
{
    return m_id;
}
