#include "golemEngine.h"

#include "Wrappers/graphicWrapper.h"
#include "Viewport/scene.h"
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
    GRAPHIC_INTERFACE->CreateFramebuffer(m_screenWidth, m_screenHeight);
}

void GolemEngine::Init()
{
    InitScene();
}

void GolemEngine::UpdateDeltaTime()
{
    static float lastFrame = 0;
    m_deltaTime = static_cast<float>(glfwGetTime()) - lastFrame;
    lastFrame = static_cast<float>(glfwGetTime());
}

void GolemEngine::ProcessInput()
{
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_window, true);
    }
}

void GolemEngine::Update()
{
    UpdateDeltaTime();
    // Bind next framebuffer to the scene buffer
    GRAPHIC_INTERFACE->BindFramebuffer();
    // Assign background color and clear previous scene buffers 
    GRAPHIC_INTERFACE->SetBackgroundColor(Vector4(0.2f, 0.3f, 0.3f, 1.0f));
    // Clear buffer
    GRAPHIC_INTERFACE->ClearBuffer();
    // Render the scene to the framebuffer
    m_scene->Update(m_screenWidth, m_screenHeight, m_window, Camera::instance, m_deltaTime);
    // Go back to original framebuffer
    GRAPHIC_INTERFACE->UnbindFramebuffer();
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