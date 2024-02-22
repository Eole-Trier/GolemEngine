#include <MathsLib/utils.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Viewport/scene.h"
#include "Resource/mesh.h"
#include "Resource/Light/point.h"

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

void Scene::RescaleFramebuffer(float width, float height)
{
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
}

void Scene::Init()
{
#pragma region VikingRoom
    Texture* text = m_resourceManager.Create<Texture>("viking_texture");
    text->Load("Assets/One_For_All/Textures/viking_room.jpg");

    Model* viking = m_resourceManager.Create<Model>("model_viking");
    viking->Load("Assets/One_For_All/Meshes/viking_room.obj");

    PointLight point1(Vector3(0.8f, 0.8f, 0.8f), Vector3(1.f, 1.f, 1.f), Vector3(1.0f, 1.0f, 1.0f), Vector3(1, 0, 0), 1.0f, 0.09f, 0.032f, 0);

    Shader* shad = m_resourceManager.Create<Shader>("viking_shader");
    shad->SetVertexAndFragmentShader("Shaders/default.vs", "Shaders/default.fs");
    point1.SetPointLight(shad);

    Mesh* mesh = m_resourceManager.Create<Mesh>("viking_mesh");
    mesh->Init(viking, text, shad);
#pragma endregion VikingRoom

    Texture* sphere_texture = m_resourceManager.Create<Texture>("all_bald_texture");
    sphere_texture->Load("Assets/One_For_All/Textures/all_bald.jpg");

    Model* sphere = m_resourceManager.Create<Model>("model_sphere");
    sphere->Load("Assets/Basics/sphere.obj");

    Shader* sphere_shad = m_resourceManager.Create<Shader>("viking_shader");
    sphere_shad->SetVertexAndFragmentShader("Shaders/default.vs", "Shaders/default.fs");

    Mesh* cube = m_resourceManager.Create<Mesh>("Lighting_Cube");
    cube->Init(sphere, sphere_texture, sphere_shad);

}

void Scene::BindFramebuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void Scene::UnbindFramebuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Scene::Render(float _width, float _height, float _deltaTime)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Shader* viking = m_resourceManager.Get<Shader>("viking_shader");

    viking->SetViewPos(camera.position);

    Matrix4 projection = Matrix4::Projection(DegToRad(camera.zoom), _width / _height, 0.1f, 1000.f);
    Matrix4 view = camera.GetViewMatrix();
    viking->SetMat4("projection", projection);
    viking->SetMat4("view", view);

    Matrix4 model = Matrix4::Identity();
    Matrix4 spherePos = Matrix4(1, 0, 0, 3, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);

    viking->SetMat4("model", model);

    Mesh* mesh = m_resourceManager.Get<Mesh>("viking_mesh");
    Mesh* light = m_resourceManager.Get<Mesh>("Lighting_Cube");
    mesh->Draw(_width, _height, camera, model);
    light->Draw(_width, _height, camera, spherePos);
}