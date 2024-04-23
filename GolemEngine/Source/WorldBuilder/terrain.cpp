#include "WorldBuilder/terrain.h"

#include <utils.h>

#include "Wrappers/graphicWrapper.h"
#include "Resource/resourceManager.h"
#include "Resource/sceneManager.h"
#include "Wrappers/windowWrapper.h"


void Terrain::SetupMesh()
{
    glGenVertexArrays(1, &p_vao);
    glGenBuffers(1, &p_vbo);
    glGenBuffers(1, &p_ebo);
    // Bindings
    glBindVertexArray(p_vao);
    glBindBuffer(GL_ARRAY_BUFFER, p_vbo);
    glBufferData(GL_ARRAY_BUFFER, p_vertices.size() * sizeof(Vertex), p_vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, p_indices.size() * sizeof(int), p_indices.data(), GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Terrain::Draw(Camera* _camera)
{
    p_shader->Use();
    p_shader->SetMat4("model", SceneManager::GetCurrentScene()->GetWorld()->transform->GetGlobalModel());
    p_shader->SetMat4("view", _camera->GetViewMatrix());
    p_shader->SetMat4("projection", Matrix4::Projection(DegToRad(_camera->GetZoom()), WindowWrapper::GetScreenSize().x / WindowWrapper::GetScreenSize().y, _camera->GetNear(), _camera->GetFar()));
    p_shader->SetFloat("maxHeight", p_yMax);
    glBindVertexArray(p_vao);
    glDrawElements(GL_LINES, (p_xResolution - 1) * (p_zResolution - 1) * 6, GL_UNSIGNED_INT, 0);
}