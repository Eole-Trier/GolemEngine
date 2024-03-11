#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <MathsLib/utils.h>

#include "Viewport/scene.h"

#include <MathsLib/utils.h>

#include "Resource/Rendering/mesh.h"
#include "Resource/tools.h"
#include "Components/Light/point.h"
#include "Components/Light/directional.h"
#include "Components/Light/spot.h"
#include "Resource/Rendering/shader.h"
#include "Core/gameobject.h"

Scene::Scene() 
{
}

void Scene::Init()
{
    #pragma region VikingRoom

    Texture* text = m_resourceManager.Create<Texture>("viking_texture");
    text->Load(Tools::FindFile("viking_room.jpg").c_str());
    
    Model* viking = m_resourceManager.Create<Model>("model_viking");
    viking->Load(Tools::FindFile("viking_room.obj").c_str());

    Shader* shad = m_resourceManager.Create<Shader>("viking_shader");
    shad->SetVertexAndFragmentShader("Shaders/default.vs", "Shaders/default.fs");
    
    InitLights();

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

void Scene::Update(float _width, float _height, GLFWwindow* _window, Camera* _camera, float _deltaTime)
{
    Shader* viking = m_resourceManager.Get<Shader>("viking_shader");

    viking->Use();

    viking->SetViewPos(_camera->position);

    UpdateLights(viking);
  
    Matrix4 model = Matrix4::Identity(); 
    Matrix4 spherePos = Matrix4(1, 0, 0, 3,
                                0, 1, 0, 0, 
                                0, 0, 1, 0, 
                                0, 0, 0, 1);

    Mesh* mesh = m_resourceManager.Get<Mesh>("viking_mesh");
    Mesh* light = m_resourceManager.Get<Mesh>("Lighting_Cube");
    mesh->Draw(_width, _height, _camera, model);
    light->Draw(_width, _height, _camera, spherePos);
}

void Scene::InitLights()
{
    // Set up the sun
    m_dirLights.push_back(new DirectionalLight(Vector4(0.4f, 0.4f, 0.4f, 0.4f), Vector4(0.05f, 0.05f, 0.05f, 0.05f), Vector4(0.5f, 0.5f, 0.5f, 0.5f), 
        Vector3(-0.2f, -1.0f, -0.3f), m_dirLights, m_maxDirLights));

    // Add some point lights
    m_pointLights.push_back(new PointLight(Vector4(1.f, 1.f, 1.f, 1.f), Vector4(1.f, 1.f, 1.f, 1.f), Vector4(1.f, 1.f, 1.f, 1.f), 
        Vector3(3, 0, 0), 1.f, 2.f, 1.f, m_pointLights, m_maxPointLights));
    m_pointLights.push_back(new PointLight(Vector4(0.8f, 0.8f, 0.8f, 0.8f), Vector4(0.05f, 0.05f, 0.05f, 0.05f), Vector4(1.0f, 1.0f, 1.0f, 1.f), 
        Vector3(0, 0, 2), 1.0f, 0.09f, 0.032f, m_pointLights, m_maxPointLights));

}

void Scene::UpdateLights(Shader* _shader)
{
    _shader->Use();

    _shader->SetInt("nbrDirectionalLights", m_dirLights.size());
    for (unsigned int i = 0; i < m_dirLights.size(); ++i)
    {
        m_dirLights[i]->SetDirectionalLight(_shader);
    }
    _shader->SetInt("nbrPointLights", m_pointLights.size());
    for (unsigned int i = 0; i < m_pointLights.size(); ++i)
    {
        m_pointLights[i]->SetPointLight(_shader);
    }

    _shader->SetInt("nbrSpotLights", m_spotLights.size());
    for (unsigned int i = 0; i < m_spotLights.size(); ++i)
    {
        m_spotLights[i]->SetSpotLight(_shader);
    }
}

