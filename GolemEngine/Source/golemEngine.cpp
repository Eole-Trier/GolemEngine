#include "golemEngine.h"

#include "Wrappers/graphicWrapper.h"
#include "Wrappers/windowWrapper.h"
#include "vector4.h"
#include "vector4.h"
#include "Viewport/scene.h"

GolemEngine::GolemEngine(int _screenWidth, int _screenHeight)
    :
    m_scene(new Scene()),
    m_screenWidth(_screenWidth),
    m_screenHeight(_screenHeight)
{}

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

    //if (glfwGetKey(m_window, GLFW_KEY_F) == GLFW_PRESS)
    //{
    //    m_engineUi->SetIsFullscreen(!m_engineUi->GetIsFullscreen());

    //    if (m_engineUi->GetIsFullscreen())
    //    {
    //        // Switch to fullscreen mode
    //        GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    //        const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
    //        glfwSetWindowMonitor(m_window, primaryMonitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    //    }
    //    else
    //    {
    //        // Switch back to windowed mode
    //        glfwSetWindowMonitor(m_window, NULL, 100, 100, m_screenWidth, m_screenHeight, GLFW_DONT_CARE);
    //    }
    //}
}

void GolemEngine::Update()
{
    WINDOW_INTERFACE->ProcessEvents();
    UpdateDeltaTime();
    //ProcessInput();
    
    // Bind next framebuffer to the scene buffer
    GRAPHIC_INTERFACE->BindFramebuffer();
    
    // Assign background color and clear previous scene buffers 
    GRAPHIC_INTERFACE->SetBackgroundColor(Vector4(0.2f, 0.3f, 0.3f, 1.0f));
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

float GolemEngine::GetScreenWidth()
{
    return m_screenWidth;
}

float GolemEngine::GetScreenHeight()
{
    return m_screenHeight;
}

