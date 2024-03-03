#include <MathsLib/utils.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Viewport/scene.h"
#include "Resource/mesh.h"
#include "Resource/tools.h"
#include "Resource/Light/point.h"
#include "Resource/Light/directional.h"
#include "Resource/Light/spot.h"
#include "Resource/shader.h"

Scene::Scene() 
{
    camera = Vector3(0.0f, 0.0f, 3.0f);
}

void Scene::CreateFramebuffer()
{
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1920, 1080, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId, 0);

    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1920, 1080);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR: Framebuffer is not complete." << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void Scene::RescaleFramebuffer(float _width, float _height)
{
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
}

void Scene::Init()
{
    #pragma region VikingRoom

    Texture* text = m_resourceManager.Create<Texture>("viking_texture");
    text->Load(FindFile("viking_room.jpg").c_str());
    
    Model* viking = m_resourceManager.Create<Model>("model_viking");
    viking->Load(FindFile("viking_room.obj").c_str());

    Shader* shad = m_resourceManager.Create<Shader>("viking_shader");
    shad->SetVertexAndFragmentShader("Shaders/default.vs", "Shaders/default.fs");
    
    InitLights(shad);

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

void Scene::BindFramebuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void Scene::UnbindFramebuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Scene::Update(float _width, float _height, GLFWwindow* _window, float _deltaTime)
{
  
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Shader* viking = m_resourceManager.Get<Shader>("viking_shader");

    viking->Use();

    viking->SetViewPos(camera.position);

    UpdateLights(viking);

  
    Matrix4 model = Matrix4::Identity(); 
    Matrix4 spherePos = Matrix4(1, 0, 0, 3,
                                0, 1, 0, 0, 
                                0, 0, 1, 0, 
                                0, 0, 0, 1);


    Mesh* mesh = m_resourceManager.Get<Mesh>("viking_mesh");
    Mesh* light = m_resourceManager.Get<Mesh>("Lighting_Cube");
    mesh->Draw(_width, _height, camera, model);
    light->Draw(_width, _height, camera, spherePos);
}

void Scene::InitLights(Shader* shader)
{
    pointLights.push_back(new PointLight(Vector4(1.f, 1.f, 1.f, 1.f), Vector4(1.f, 1.f, 1.f, 1.f), Vector4(1.f, 1.f, 1.f, 1.f), Vector3(3, 0, 0), 1.f, 2.f, 1.f, 0));
    pointLights.push_back(new PointLight(Vector4(0.8f, 0.8f, 0.8f, 0.8f), Vector4(0.05f, 0.05f, 0.05f, 0.05f), Vector4(1.0f, 1.0f, 1.0f, 1.f), Vector3(0, 0, 2), 1.0f, 0.09f, 0.032f, 1));
    dirLights.push_back(new DirectionalLight(Vector4(0.4f, 0.4f, 0.4f, 0.4f), Vector4(0.05f, 0.05f, 0.05f, 0.05f), Vector4(0.5f, 0.5f, 0.5f, 0.5f), Vector3(-0.2f, -1.0f, -0.3f), 0));
}

void Scene::UpdateLights(Shader* shader)
{
    shader->Use();

    shader->SetInt("nbrDirectionalLights", dirLights.size());
    for (unsigned int i = 0; i < dirLights.size(); ++i)
    {
        dirLights[i]->SetDirectionalLight(shader);
    }

    shader->SetInt("nbrPointLights", pointLights.size());
    for (unsigned int i = 0; i < pointLights.size(); ++i)
    {
        pointLights[i]->SetPointLight(shader);
    }

    shader->SetInt("nbrSpotLights", spotLights.size());
    for (unsigned int i = 0; i < spotLights.size(); ++i)
    {
        spotLights[i]->SetSpotLight(shader);
    }
}

