#include <MathsLib/utils.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Viewport/scene.h"
#include "Resource/mesh.h"
#include "Resource/Light/point.h"

Scene::Scene() 
{
    Camera = Vector3(0.0f, 0.0f, 3.0f);
}

void Scene::Init()
{
    Texture* text = m_resourceManager.Create<Texture>("viking_texture");
    text->Load("Assets/One_For_All/Textures/viking_room.jpg");
    
    Model* viking = m_resourceManager.Create<Model>("model_viking");
    viking->Load("Assets/One_For_All/Meshes/viking_room.obj", "Assets/One_For_All/Textures/viking_room.jpg");

    PointLight point1(Vector3(0.8f, 0.8f, 0.8f), Vector3(1.f, 1.f, 1.f), Vector3(1.0f, 1.0f, 1.0f), Vector3(1, 0, 0), 1.0f, 0.09f, 0.032f, 0);

    Shader* shad = m_resourceManager.Create<Shader>("viking_shader");
    shad->SetVertexAndFragmentShader("Shaders/default.vert", "Shaders/default.frag");
    point1.SetPointLight(shad);

    shad->Use();

    Mesh* mesh = m_resourceManager.Create<Mesh>("viking_mesh");
    mesh->Init(viking, text, shad);
}

void Scene::Update(float _width, float _height, GLFWwindow* _window, float _deltaTime)
{

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Shader* viking = m_resourceManager.Get<Shader>("viking_shader");
  
    viking->SetViewPos(Camera.Position);

    Matrix4 projection = Matrix4::Projection(DegToRad(Camera.Zoom), _width / _height, 0.1f, 1000.f);
    Matrix4 view = Camera.GetViewMatrix();
    viking->SetMat4("projection", projection);
    viking->SetMat4("view", view);

    Matrix4 model = Matrix4::Identity(); 
    viking->SetMat4("model", model);

    Mesh* mesh = m_resourceManager.Get<Mesh>("viking_mesh");
    mesh->Draw(_width, _height, Camera, model);
}

