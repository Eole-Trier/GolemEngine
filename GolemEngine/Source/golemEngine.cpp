#include <wtypes.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "UI/engineUi.h"
#include "Wrappers/interfaceWrapper.h"
#include "Wrappers/graphicWrapper.h"
#include "vector4.h"

#include "golemEngine.h"

#include "UI/engineUi.h"
#include "UI/Windows/viewport.h"


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
    // Init glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // Create window
    m_window = glfwCreateWindow(m_screenWidth, m_screenHeight, m_name.c_str(), NULL, NULL);
    if (m_window == NULL)
    {
        std::cout << "Failed to create GLFW window : " << m_name << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(m_window);
   
    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    InterfaceWrapper::GetInstance()->Init(m_window);

}

void GolemEngine::InitScene()
{
    // Init scene objects
    m_scene->Init();
    // Create a framebuffer and pass the scene in it to be used in the viewport 
    GraphicWrapper::GetInstance()->CreateFramebuffer(m_screenWidth, m_screenHeight);
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
    while (!glfwWindowShouldClose(m_window))
    {
        glfwPollEvents();
        UpdateDeltaTime();
        ProcessInput();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Bind next framebuffer to the scene buffer
        GraphicWrapper::GetInstance()->BindFramebuffer();
        // Assign background color and clear previous scene buffers 
        GraphicWrapper::GetInstance()->SetBackgroundColor(Vector4(0.2f, 0.3f, 0.3f, 1.0f));
        GraphicWrapper::GetInstance()->ClearBuffer();
        // Render the scene to the framebuffer
        m_scene->Update(m_screenWidth, m_screenHeight, m_window, m_engineUi->GetViewport()->GetCamera(), m_deltaTime);
        // Go back to original framebuffer
        GraphicWrapper::GetInstance()->UnbindFramebuffer();

        m_engineUi->BeginDockSpace();

        InterfaceWrapper::GetInstance()->Loop();

        glfwSwapBuffers(m_window);
    }
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