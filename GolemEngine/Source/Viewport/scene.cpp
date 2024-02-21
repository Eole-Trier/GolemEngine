#include <MathsLib/utils.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Viewport/scene.h"
#include "Resource/mesh.h"
#include "Resource/Light/point.h"
#include "Resource/Light/directional.h"

Scene::Scene() 
{
    Camera = Vector3(0.0f, 0.0f, 3.0f);
}

void Scene::Init()
{
    #pragma region VikingRoom

    Texture* text = m_resourceManager.Create<Texture>("viking_texture");
    text->Load("Assets/One_For_All/Textures/viking_room.jpg");
    
    Model* viking = m_resourceManager.Create<Model>("model_viking");
    viking->Load("Assets/One_For_All/Meshes/viking_room.obj");

    Shader* shad = m_resourceManager.Create<Shader>("viking_shader");
    shad->SetVertexAndFragmentShader("Shaders/default.vs", "Shaders/default.fs");
    shad->Use();
    shad->SetInt("nbrPointLights", 2);
    shad->SetInt("nbrDirLights", 1);


    Mesh* mesh = m_resourceManager.Create<Mesh>("viking_mesh");
    mesh->Init(viking, text, shad);
    #pragma endregion VikingRoom

    Texture* sphere_texture = m_resourceManager.Create<Texture>("all_bald_texture");
    sphere_texture->Load("Assets/One_For_All/Textures/all_bald.jpg");

    Model* sphere = m_resourceManager.Create<Model>("model_sphere");
    sphere->Load("Assets/Basics/sphere.obj");

    Mesh* cube = m_resourceManager.Create<Mesh>("Lighting_Cube");
    cube->Init(sphere, sphere_texture, shad);

}

void Scene::Update(float _width, float _height, GLFWwindow* _window, float _deltaTime)
{
  
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Shader* viking = m_resourceManager.Get<Shader>("viking_shader");

    viking->Use();

    viking->SetViewPos(Camera.Position);

    PointLight point1(Vector4(1.f, 1.f, 1.f, 1.f), Vector4(1.f, 1.f, 1.f, 1.f), Vector4(1.f, 1.f, 1.f, 1.f), Vector3(3, 0, 0), 1.f, 2.f, 1.f, 0);
    PointLight point2(Vector4(0.8f, 0.8f, 0.8f, 0.8f), Vector4(0.05f, 0.05f, 0.05f, 0.05f), Vector4(1.0f, 1.0f, 1.0f, 1.f), Vector3(0, 0, 2), 1.0f, 0.09f, 0.032f, 1);
    DirectionalLight dir1(Vector4(0.4f, 0.4f, 0.4f, 0.4f), Vector4(0.05f, 0.05f, 0.05f, 0.05f), Vector4(0.5f, 0.5f, 0.5f, 0.5f), Vector3(-0.2f, -1.0f, -0.3f), 0);

    point1.SetPointLight(viking);
    point2.SetPointLight(viking);
    dir1.SetDirectionalLight(viking);

  
    Matrix4 model = Matrix4::Identity(); 
    Matrix4 spherePos = Matrix4(1, 0, 0, 3,
                                0, 1, 0, 0, 
                                0, 0, 1, 0, 
                                0, 0, 0, 1);


    Mesh* mesh = m_resourceManager.Get<Mesh>("viking_mesh");
    Mesh* light = m_resourceManager.Get<Mesh>("Lighting_Cube");
    mesh->Draw(_width, _height, Camera, model);
    light->Draw(_width, _height, Camera, spherePos);
}

