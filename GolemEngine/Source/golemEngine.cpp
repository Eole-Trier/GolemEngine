#include "golemEngine.h"

#include "Wrappers/graphicWrapper.h"
#include "Wrappers/windowWrapper.h"
#include "Resource/sceneManager.h"
#include "Core/scene.h"
#include "Core/camera.h"
#include "Inputs/inputManager.h"
#include "vector4.h"
#include "Reflection/classesManager.h"


void GolemEngine::Init()
{
    ClassesManager::AddAllClasses();
    SceneManager::Init();
    InputManager::Init(WindowWrapper::window);
    m_camera = new Camera();
}

void GolemEngine::UpdateDeltaTime()
{
    static float lastFrame = 0;
    m_deltaTime = static_cast<float>(glfwGetTime()) - lastFrame;
    lastFrame = static_cast<float>(glfwGetTime());
}

void GolemEngine::ProcessInput()
{
    if (InputManager::IsKeyPressed(KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(WindowWrapper::window, true);
    }
}

void GolemEngine::Update()
{
    UpdateDeltaTime();
    // Bind next framebuffer to the scene buffer
    GraphicWrapper::BindFramebuffer();
    // Assign background color and clear previous scene buffers
    GraphicWrapper::SetBackgroundColor(Vector4(0.2f, 0.3f, 0.3f, 1.0f));
    // Clear buffer
    GraphicWrapper::ClearBuffer();
    // Render the scene to the framebuffer
    //for (int i = 0; i < texList.size(); i++)
    //{
        SceneManager::GetCurrentScene()->Update(WindowWrapper::GetScreenSize().x, WindowWrapper::GetScreenSize().y, m_camera);
    //}

    // Go back to original framebuffer
    GraphicWrapper::UnbindFramebuffer();
}

void GolemEngine::Close()
{
    glfwTerminate();
}

Camera* GolemEngine::GetCamera()
{
    return m_camera;
}

float GolemEngine::GetDeltaTime()
{
    return m_deltaTime;
}

float GolemEngine::GetTime()
{
    return static_cast<float>(glfwGetTime());
}