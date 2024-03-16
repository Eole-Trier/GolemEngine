#include "golemEngine.h"

#include "Wrappers/graphicWrapper.h"
#include "Wrappers/windowWrapper.h"
#include "Viewport/scene.h"
#include "Viewport/camera.h"
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
    
    GraphicWrapper::CreateFramebuffer(m_screenWidth, m_screenHeight);
}

void GolemEngine::Init()
{
    InitScene();
    InputManager::Init(m_window);
    m_camera = new Camera(m_window);
    InputManager::SetCamera(m_camera);
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
    UpdateDeltaTime();
    // Bind next framebuffer to the scene buffer
    GraphicWrapper::BindFramebuffer();
    // Assign background color and clear previous scene buffers 
    GraphicWrapper::SetBackgroundColor(Vector4(0.2f, 0.3f, 0.3f, 1.0f));
    // Clear buffer
    GraphicWrapper::ClearBuffer();
    // Render the scene to the framebuffer
    m_scene->Update(m_screenWidth, m_screenHeight, m_camera, m_deltaTime);
    // Go back to original framebuffer
    GraphicWrapper::UnbindFramebuffer();
}

void GolemEngine::Close()
{
    glfwTerminate();
}

GLFWwindow* GolemEngine::GetWindow()
{
    return m_window;
}

Camera* GolemEngine::GetCamera()
{
    return m_camera;
}

Scene* GolemEngine::GetScene()
{
    return m_scene;
}

float GolemEngine::GetDeltaTime()
{
    return m_deltaTime;
}

float GolemEngine::GetTime()
{
    return static_cast<float>(glfwGetTime());
}

void GolemEngine::SetScreenSize(const int _width, const int _height)
{
    m_screenWidth = _width;
    m_screenHeight = _height;
}

void GolemEngine::SetWindow(GLFWwindow* _window)
{
    m_window = _window;
}