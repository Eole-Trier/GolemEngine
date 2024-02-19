#include <MathsLib/utils.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Viewport/scene.h"
#include "Resource/mesh.h"

Scene::Scene() 
{
    m_camera = Vector3(0.0f, 0.0f, 3.0f);
}

void Scene::Init()
{
    Texture* text = m_resourceManager.Create<Texture>("viking_texture");
    text->Load("Assets/One_For_All/Textures/viking_room.jpg");

    Shader* shad = m_resourceManager.Create<Shader>("viking_shader");
    shad->SetVertexAndFragmentShader("Shaders/lighting.vs", "Shaders/lighting.fs");

    Model* viking = m_resourceManager.Create<Model>("model_viking");
    viking->Load("Assets/One_For_All/Meshes/viking_room.obj", "Assets/One_For_All/Textures/viking_room.jpg");

    Mesh* mesh = m_resourceManager.Create<Mesh>("viking_mesh");
    mesh->Init(viking, text, shad);
}

void Scene::Update(float _width, float _height)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Shader* viking = m_resourceManager.Get<Shader>("viking_shader");
    viking->Use();
    viking->SetViewPos(m_camera.Position);

    Matrix4 projection = Matrix4::Projection(DegToRad(m_camera.Zoom), _width / _height, 0.1f, 1000.f);
    Matrix4 view = m_camera.GetViewMatrix();
    viking->SetMat4("projection", projection);
    viking->SetMat4("view", view);

    Matrix4 model = Matrix4::Identity();
    viking->SetMat4("model", model);

    Mesh* mesh = m_resourceManager.Get<Mesh>("viking_mesh");
    mesh->Draw(_width, _height, m_camera, model);
}
