#include "golemEngine.h"

#include <wtypes.h>

#include "UI/engineUi.h"
#include "Wrappers/graphicWrapper.h"
#include "Wrappers/windowWrapper0.h"
#include "vector4.h"
#include "UI/engineUi.h"
#include "UI/Windows/viewport.h"
#include "vector4.h"
#include "Viewport/scene.h"

GolemEngine::GolemEngine()
    :
    m_name("Golem Engine"),
    m_scene(new Scene()),
    m_engineUi(new EngineUi(this))
{
    // Get screen dimensions
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);

    m_screenWidth = desktop.right;
    m_screenHeight = desktop.bottom;
}

void GolemEngine::InitWindow()
{
    WINDOW_INTERFACE->Init();
    WINDOW_INTERFACE->SetOption(OPENGL_MAJOR_VERSION, 3);
    WINDOW_INTERFACE->SetOption(OPENGL_MINOR_VERSION, 0);

    // Create window
    m_window = WINDOW_INTERFACE->NewWindow(m_screenWidth, m_screenHeight, m_name.c_str(), NULL, NULL);
    if (m_window == NULL)
    {
        std::cout << "Failed to create GLFW window : " << m_name << std::endl;
        WINDOW_INTERFACE->Terminate();
    }

    WINDOW_INTERFACE->SetCurrentWindow(m_window);

    // Initialize GLAD
    if (!GRAPHIC_INTERFACE->Init())

    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    m_engineUi->InitUI(m_window);
}

void GolemEngine::InitScene()
{
    // Init scene objects
    m_scene->Init();
    // Create a framebuffer and pass the scene in it to be used in the viewport 
    GRAPHIC_INTERFACE->CreateFramebuffer(m_screenWidth, m_screenHeight);
}

void GolemEngine::Init()
{
    InitWindow();
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

    if (glfwGetKey(m_window, GLFW_KEY_F) == GLFW_PRESS)
    {
        m_engineUi->SetIsFullscreen(!m_engineUi->GetIsFullscreen());

        if (m_engineUi->GetIsFullscreen())
        {
            // Switch to fullscreen mode
            GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
            const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
            glfwSetWindowMonitor(m_window, primaryMonitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        }
        else
        {
            // Switch back to windowed mode
            glfwSetWindowMonitor(m_window, NULL, 100, 100, m_screenWidth, m_screenHeight, GLFW_DONT_CARE);
        }
    }
}

void GolemEngine::Update()
{
    WINDOW_INTERFACE->ProcessEvents();
    UpdateDeltaTime();
    ProcessInput();
    
    // Bind next framebuffer to the scene buffer
    GRAPHIC_INTERFACE->BindFramebuffer();
    
    // Assign background color and clear previous scene buffers 
    GRAPHIC_INTERFACE->SetBackgroundColor(Vector4(0.2f, 0.3f, 0.3f, 1.0f));
    GRAPHIC_INTERFACE->ClearBuffer();
    
    // Render the scene to the framebuffer
    m_scene->Update(m_screenWidth, m_screenHeight, m_window, m_engineUi->GetViewport()->GetCamera(), m_deltaTime);
    
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

EngineUi* GolemEngine::GetUi()
{
    return m_engineUi;
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

