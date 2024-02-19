#include "Resource/mesh.h"

#include <MathsLib/utils.h>

#include "../../Libraries/Include/glad/glad.h"

void Mesh::SetupMesh()
{
    glGenVertexArrays(1, &m_model->VAO);

    glGenBuffers(1, &m_model->VBO);
    glBindVertexArray(m_model->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_model->VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_model->vertices.size(), m_model->vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TextureCoords));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

Mesh::Mesh() {}

Mesh::~Mesh() 
{
    glDeleteVertexArrays(1, &m_model->VAO);
    glDeleteBuffers(1, &m_model->VBO);
}

void Mesh::Init(Model* _model, Texture* _texture, Shader* _shader) 
{
    m_model = _model;
    m_texture = _texture;
    m_shader = _shader;
    SetupMesh();
}

void Mesh::Draw(float _width, float _height, Camera& _cam, const Matrix4& _localModel)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture->id);

    m_shader->Use();

    Matrix4 model = _localModel;
    Matrix4 view = _cam.GetViewMatrix();
    Matrix4 projection = Matrix4::Projection(DegToRad(_cam.Zoom), _width / _height, _cam.Near, _cam.Far);

    m_shader->SetMat4("model", model);
    m_shader->SetMat4("view", view);
    m_shader->SetMat4("projection", projection);

    glBindVertexArray(m_model->VAO);
    glDrawArrays(GL_TRIANGLES, 0, m_model->vertices.size());
}