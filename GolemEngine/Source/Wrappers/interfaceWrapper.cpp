#include "Wrappers/interfaceWrapper.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Viewport/camera.h"

InterfaceWrapper* InterfaceWrapper::m_instancePtr = nullptr;

InterfaceWrapper* InterfaceWrapper::GetInstance()
{
    return m_instancePtr;
}

InterfaceWrapper::InterfaceWrapper() {}

InterfaceWrapper::~InterfaceWrapper() {}

void InterfaceWrapper::Init(GLFWwindow* _window)
{
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

    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

void InterfaceWrapper::NewFrameImGui()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void InterfaceWrapper::EditorStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowRounding = 4;
    style.FrameRounding = 4;
    style.GrabRounding = 3;
    style.ScrollbarSize = 7;
    style.ScrollbarRounding = 0;
}

void InterfaceWrapper::End()
{
    ImGui::End();
}

void InterfaceWrapper::Render()
{
    ImGui::Render();
}

void InterfaceWrapper::Begin(const char* _name)
{
    ImGui::Begin(_name);
}

void InterfaceWrapper::Dock()
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
    if (init)
    {
        ImGuiID dock_id_left, dock_id_right;
        init = false;
        ImGui::DockBuilderAddNode(dockspace_id);
        ImGui::DockBuilderSetNodeSize(dockspace_id, ImGui::GetMainViewport()->Size);

        ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.8f, &dock_id_left, &dock_id_right);

        ImGuiID dock_id_topRight, dock_id_bottomRight;
        ImGui::DockBuilderSplitNode(dock_id_right, ImGuiDir_Up, 0.8f, &dock_id_topRight, &dock_id_bottomRight);

        ImGuiID dock_id_topLeft, dock_id_bottomLeft;
        ImGui::DockBuilderSplitNode(dock_id_left, ImGuiDir_Up, 0.8f, &dock_id_topLeft, &dock_id_bottomLeft);

        ImGui::DockBuilderDockWindow("Basic_Actors", dock_id_topRight);
        ImGui::DockBuilderDockWindow("File_Browser", dock_id_bottomLeft);
        ImGui::DockBuilderDockWindow("Viewport", dock_id_topLeft);
        ImGui::DockBuilderDockWindow("World_Actors", dock_id_topRight);
        ImGui::DockBuilderDockWindow("Debug", dock_id_bottomRight);

        ImGui::DockBuilderFinish(dockspace_id);
    }

    if (optFullscreen)
    {
        ImGui::PopStyleVar(3);
    }
}

void InterfaceWrapper::Loop()
{
    ImGuiIO& io = ImGui::GetIO();
    Camera* camera = Camera::instance;

    Begin("Camera");

    ImGui::SliderFloat("Camera Move Speed : ",  &camera->movementSpeed, 0, 30.0f, 0);
    ImGui::SliderFloat("Camera Move Sensitivity : ", &camera->mouseSensitivity, 0, 2.0f, 0);

    End();

    Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

