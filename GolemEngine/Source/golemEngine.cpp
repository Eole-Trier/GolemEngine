#include "golemEngine.h"

#include <wtypes.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "UI/engineUi.h"
#include "Wrappers/interfaceWrapper.h"


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

    m_scene->width = m_screenWidth;
    m_scene->height = m_screenHeight;
}

GolemEngine::~GolemEngine() {}

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

   // Set fullscreen
   //m_monitor = glfwGetPrimaryMonitor();
   //const GLFWvidmode* mode = glfwGetVideoMode(m_monitor);
   //glfwSetWindowMonitor(m_window, m_monitor, 0, 0, mode->width, mode->height, mode->refreshRate);

    glfwMakeContextCurrent(m_window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    InterfaceWrapper::GetInstance()->InitImGui(m_window);
}

void GolemEngine::InitScene()
{
    // Init scene objects
    m_scene->Init();
    // Create a framebuffer and pass the scene in it to be used in the viewport 
    m_scene->CreateFramebuffer();
}

void GolemEngine::Init()
{
    InitWindow();
    InitScene();
}

Scene* GolemEngine::GetScene()
{
    return m_scene;
}

GLFWwindow* GolemEngine::GetGLFWWindow()
{
    return m_window;
}

void GolemEngine::UpdateDeltaTime()
{
    static float lastFrame = 0;
    m_deltaTime = static_cast<float>(glfwGetTime()) - lastFrame;
    lastFrame = static_cast<float>(glfwGetTime());
}

float GolemEngine::GetDeltaTime()
{
    return m_deltaTime;
}

float GolemEngine::GetTime()
{
    return static_cast<float>(glfwGetTime());
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
    glViewport(0, 0, m_screenWidth, m_screenHeight);
    while (!glfwWindowShouldClose(m_window))
    {
        glfwPollEvents();
        UpdateDeltaTime();
        ProcessInput();

        InterfaceWrapper::GetInstance()->NewFrameImGui();
        InterfaceWrapper::GetInstance()->EditorStyle();

#pragma region DockSpace;

        m_engineUi->BeginDockSpace();


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Bind next framebuffer to the scene buffer
        m_scene->BindFramebuffer();
        // Clear previous scene buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Render the scene to the framebuffer
        m_scene->Update(m_screenWidth, m_screenHeight, m_window, m_deltaTime);
        // Go back to original framebuffer
        m_scene->UnbindFramebuffer();

        m_engineUi->EndDockSpace();

#pragma endregion DockSpace

        InterfaceWrapper::GetInstance()->LoopImGui();
        
        glfwSwapBuffers(m_window);
    }
}

void GolemEngine::Close() 
{
    glfwTerminate();
}