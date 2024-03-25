#include "golemEngine.h"

#include "Wrappers/graphicWrapper.h"
#include "Wrappers/windowWrapper.h"
#include "Viewport/scene.h"
#include "Viewport/camera.h"
#include "inputManager.h"
#include "vector4.h"

GolemEngine* GolemEngine::m_golemInstance = nullptr;

GolemEngine* GolemEngine::GetInstance()
{
    if (m_golemInstance == nullptr) 
    {
        m_golemInstance = new GolemEngine();
    }
    return m_golemInstance;
}


GolemEngine::GolemEngine()
    :
    m_scene(new Scene())
{}

GolemEngine::~GolemEngine() {}

void GolemEngine::InitScene()
{
    // Init scene objects
    m_scene->Init();
    // Create a framebuffer and pass the scene in it to be used in the viewport 
    
    GraphicWrapper::CreateFramebuffer(WindowWrapper::GetScreenSize().x, WindowWrapper::GetScreenSize().y);
}

void GolemEngine::Init()
{
    InitScene();
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
    m_scene->Update(WindowWrapper::GetScreenSize().x, WindowWrapper::GetScreenSize().y, m_camera);
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

Scene* GolemEngine::GetScene()
{
    return m_scene;
}



GLFWwindow* GolemEngine::GetWindow()
{
    return m_window;
}

float GolemEngine::GetDeltaTime()
{
    return m_deltaTime;
}

float GolemEngine::GetTime()
{
    return static_cast<float>(glfwGetTime());
}