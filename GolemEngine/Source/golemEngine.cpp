#include "golemEngine.h"

#include <wtypes.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "UI/engineUi.h"
#include "Wrappers/openglWrapper.h"
#include "vector4.h"


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

    // Setup Imgui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // Setup style
    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

void GolemEngine::InitScene()
{
    // Init scene objects
    m_scene->Init();
    // Create a framebuffer and pass the scene in it to be used in the viewport 
    OpenglWrapper::GetInstance()->CreateFramebuffer(m_screenWidth, m_screenHeight);
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
}

void GolemEngine::Update()
{
    ImGuiIO& io = ImGui::GetIO();
    glViewport(0, 0, m_screenWidth, m_screenHeight);
    while (!glfwWindowShouldClose(m_window))
    {
        glfwPollEvents();

        UpdateDeltaTime();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

#pragma region DockSpace;
        m_engineUi->BeginDockSpace();
        
        ProcessInput();

        ImVec2 pos = ImGui::GetCursorScreenPos();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Bind next framebuffer to the scene buffer
        OpenglWrapper::GetInstance()->BindFramebuffer();
        // Assign background color and clear previous scene buffers 
        OpenglWrapper::GetInstance()->SetBackgroundColor(Vector4(0.2f, 0.3f, 0.3f, 1.0f));
        OpenglWrapper::GetInstance()->ClearBuffer();
        // Render the scene to the framebuffer
        m_scene->Update(m_screenWidth, m_screenHeight, m_window, m_deltaTime);
        // Go back to original framebuffer
        OpenglWrapper::GetInstance()->UnbindFramebuffer();
        
        m_engineUi->EndDockSpace();
#pragma enderegion DockSpace

        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

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

GLFWwindow* GolemEngine::GetGlfwWindow()
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