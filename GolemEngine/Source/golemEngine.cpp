#include "golemEngine.h"

#include "Wrappers/graphicWrapper.h"
#include "Viewport/scene.h"
#include "inputManager.h"
#include "vector4.h"

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
    GraphicWrapper* graphicWrapper = GraphicWrapper::GetInstance();
    graphicWrapper->CreateFramebuffer(m_screenWidth, m_screenHeight);
}

void GolemEngine::Init()
{
    InitScene();
    InputManager::Init(m_window);
    
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
        glfwSetWindowShouldClose(m_window, true);
    }
}

void GolemEngine::Update()
{
    GraphicWrapper* graphicWrapper = GraphicWrapper::GetInstance();
     
    UpdateDeltaTime();
    // Bind next framebuffer to the scene buffer
    graphicWrapper->BindFramebuffer();
    // Assign background color and clear previous scene buffers 
    graphicWrapper->SetBackgroundColor(Vector4(0.2f, 0.3f, 0.3f, 1.0f));
    // Clear buffer
    graphicWrapper->ClearBuffer();
    // Render the scene to the framebuffer
    m_scene->Update(m_screenWidth, m_screenHeight, m_window, Camera::instance, m_deltaTime);
    // Go back to original framebuffer
    graphicWrapper->UnbindFramebuffer();
}

void GolemEngine::Close()
{
    glfwTerminate();
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

void GolemEngine::SetScreenSize(int _width, int _height)
{
    m_screenWidth = _width;
    m_screenHeight = _height;
}

void GolemEngine::SetWindow(GLFWwindow* _window)
{
    m_window = _window;
}