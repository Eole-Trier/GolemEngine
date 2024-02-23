#include "UI\engineWindow.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <wtypes.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

EngineWindow::EngineWindow(const char* _name)
    : m_name(_name)
{
    // Get screen dimensions
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    screenWidth = desktop.right;
    screenHeight = desktop.bottom;

    scene = new Scene();
    scene->width = screenWidth;
    scene->height = screenHeight;
    m_viewport = new Viewport();
    m_basicActors = new BasicActors();
    m_fileBrowser = new FileBrowser();
    m_debugWindow = new DebugWindow();
}

EngineWindow::~EngineWindow() {}

void EngineWindow::Init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // Create window
    m_window = glfwCreateWindow(screenWidth, screenHeight, m_name.c_str(), NULL, NULL);
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
    //glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
    glfwSwapInterval(1);    // Enable vsync


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    //glEnable(GL_DEPTH_TEST);  //

    // Setup Imgui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // Setup style
    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 460");

    // Init scene and scene framebuffer to pass it to the viewport later
    scene->Init();
    scene->CreateFramebuffer();
}

void EngineWindow::UpdateDeltaTime()
{
    static float lastDeltaTime = 0.0f;
    time = static_cast<float>(glfwGetTime());
    deltaTime = time - m_lastFrame;
    m_lastFrame = time;
}

void EngineWindow::ImGuiLoop()
{
    m_basicActors->Render();
    m_fileBrowser->Render();
    m_viewport->Render(scene);
    m_debugWindow->Render(this);
}

void EngineWindow::BeginDockSpace()
{
    static bool dockspaceOpen = true;
    static bool optFullscreenPersistant = true;
    const bool optFullscreen = optFullscreenPersistant;

    ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;
    if (optFullscreen)
    {
        dockspaceFlags |= ImGuiDockNodeFlags_PassthruCentralNode;
    }

    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (optFullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });

        windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;
    }

    ImGui::Begin("DockSpace Demo", &dockspaceOpen, windowFlags);

    ImGuiID dockspace_id = ImGui::GetID("DockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspaceFlags);

    static bool init = true;
    ImGuiID dock_id_left, dock_id_right;
    if (init) 
    {
        init = false;
        ImGui::DockBuilderRemoveNode(dockspace_id);
        ImGui::DockBuilderAddNode(dockspace_id);
        ImGui::DockBuilderSetNodeSize(dockspace_id, ImGui::GetMainViewport()->Size);

        ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.5f, &dock_id_left, &dock_id_right);

        ImGuiID dock_id_topRight, dock_id_bottomRight;
        ImGui::DockBuilderSplitNode(dock_id_right, ImGuiDir_Up, 0.5f, &dock_id_topRight, &dock_id_bottomRight);

        ImGuiID dock_id_topLeft, dock_id_bottomLeft;
        ImGui::DockBuilderSplitNode(dock_id_left, ImGuiDir_Up, 0.5f, &dock_id_topLeft, &dock_id_bottomLeft);

        ImGui::DockBuilderDockWindow("Basic_Actors", dock_id_topLeft);
        ImGui::DockBuilderDockWindow("File_Browser", dock_id_topRight);
        ImGui::DockBuilderDockWindow("Viewport", dock_id_bottomRight);
        ImGui::DockBuilderDockWindow("Debug", dock_id_bottomLeft);

        ImGui::DockBuilderFinish(dockspace_id);
    }

    if (optFullscreen)
    {
        ImGui::PopStyleVar(3);
    }

    ImGuiLoop();
}

void EngineWindow::EndDockSpace()
{
    ImGui::End();
}

void EngineWindow::ProcessInput()
{
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_window, true);
    }
}

void EngineWindow::Render()
{
    ImGuiIO& io = ImGui::GetIO();
    glViewport(0, 0, screenWidth, screenHeight);
    while (!glfwWindowShouldClose(m_window))
    {
        glfwPollEvents();

        UpdateDeltaTime();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

#pragma region Dockspace
        BeginDockSpace();

        ProcessInput();

        ImVec2 pos = ImGui::GetCursorScreenPos();
        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

        // Bind next framebuffer to the scene buffer
        scene->BindFramebuffer();
        // Clear previous scene buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Render the scene to the framebuffer
        scene->Render(screenWidth, screenHeight, deltaTime);
        // Go back to original framebuffer
        scene->UnbindFramebuffer();

        EndDockSpace();
#pragma endregion Dockspace

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

    glDeleteFramebuffers(1, &scene->fbo);
    glDeleteTextures(1, &scene->textureId);
    glDeleteRenderbuffers(1, &scene->rbo);

    Close();
}

void EngineWindow::Close()
{
    glfwTerminate();
}

void EngineWindow::ImGuiClean() {}
