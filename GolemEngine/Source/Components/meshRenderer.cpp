#include "Components/meshRenderer.h"

#include "Wrappers/graphicWrapper.h"
#include "MathsLib/utils.h"
#include "Resource/Rendering/texture.h"
#include "Resource/Rendering/model.h"


MeshRenderer::MeshRenderer()
{}

MeshRenderer::MeshRenderer(Mesh* _mesh)
    : m_mesh(_mesh)
{}

MeshRenderer::~MeshRenderer()
{}

void MeshRenderer::Draw(float _width, float _height, Camera* _camera)
{   
    if (m_mesh)
    {
        Texture* texture = m_mesh->GetTexture();
        Model* model = m_mesh->GetModel();
        Shader* shader = m_mesh->GetShader();

        glActiveTexture(GL_TEXTURE0);
        texture->Use();

        shader->Use();

        Matrix4 view = _camera->GetViewMatrix();
        Matrix4 projection = Matrix4::Projection(DegToRad(_camera->GetZoom()), _width / _height, _camera->GetNear(), _camera->GetFar());
        shader->SetMat4("model", owner->transform->GetGlobalModel());
        shader->SetMat4("view", view);
        shader->SetMat4("projection", projection);

        glBindVertexArray(model->VAO);
        glDrawArrays(GL_TRIANGLES, 0, model->vertices.size());
    }
}

Mesh* MeshRenderer::GetMesh()
{
    return  m_mesh;
}
