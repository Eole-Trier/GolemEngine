#include "Components/meshRenderer.h"

#include "Wrappers/graphicWrapper.h"
#include "MathsLib/utils.h"
#include "Resource/Rendering/texture.h"
#include "Resource/Rendering/model.h"

MeshRenderer::MeshRenderer()
{
}

MeshRenderer::MeshRenderer(Mesh* _mesh)
    : m_mesh(_mesh)
{
}

MeshRenderer::~MeshRenderer()
{
    delete m_mesh;
}

void MeshRenderer::Draw(float _width, float _height, Camera* _cam)
{   
    if (m_mesh)
    {
        Texture* texture = m_mesh->GetTexture();
        Model* model = m_mesh->GetModel();
        Shader* shader = m_mesh->GetShader();

        glActiveTexture(GL_TEXTURE0);
        texture->Use();

        shader->Use();

        Matrix4 view = _cam->GetViewMatrix();
        Matrix4 projection = Matrix4::Projection(DegToRad(_cam->GetZoom()), _width / _height, _cam->GetNear(), _cam->GetFar());
        shader->SetMat4("view", view);
        shader->SetMat4("projection", projection);
        shader->SetMat4("model", owner->transform->GetGlobalModel());

        glBindVertexArray(model->VAO);
        glDrawArrays(GL_TRIANGLES, 0, model->vertices.size());
    }
}
