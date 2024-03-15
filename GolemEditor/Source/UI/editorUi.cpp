#include "UI/editorUi.h"

#include "golemEngine.h"
#include "Ui/Windows/basicActors.h"
#include "Ui/Windows/viewport.h"
#include "Ui/Windows/fileBrowser.h"
#include "Ui/Windows/sceneGraph.h"
#include "Ui/Windows/debugWindow.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"


EditorUi::EditorUi(GolemEngine* _golemEngine)
    :
    m_golemEngine(_golemEngine),
    m_viewport(new Viewport("Viewport")),
    m_basicActors(new BasicActors("Basic_Actors")),
    m_fileBrowser(new FileBrowser("File_Browser")),
    m_sceneGraph(new SceneGraph("Scene_Graph")),
    m_debugWindow(new DebugWindow("Debug"))
{
}

void EditorUi::Init(GLFWwindow* _window)
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

    style.WindowRounding = 4;
    style.FrameRounding = 4;
    style.GrabRounding = 3;
    style.ScrollbarSize = 7;
    style.ScrollbarRounding = 0;
}

void EditorUi::BeginDockSpace()
{
#pragma region Setup dockspace
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
#pragma endregion Setup dockspace

#pragma region Create dockspace
    ImGui::Begin("DockSpace Demo", &dockspaceOpen, windowFlags);

    ImGuiID dockspace_id = ImGui::GetID("DockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspaceFlags);

    // Dock Control Space
    static bool init = true;
    ImGuiID dock_id_left, dock_id_right;
    if (init)
    {
        // The dock has a default 4 block layout
        // Topleft     TopRight
        // Bottomlefr  BottomRight
        init = false;
        ImGui::DockBuilderRemoveNode(dockspace_id);
        ImGui::DockBuilderAddNode(dockspace_id);
        ImGui::DockBuilderSetNodeSize(dockspace_id, ImGui::GetMainViewport()->Size);

        ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.8f, &dock_id_left, &dock_id_right);

        ImGuiID dock_id_topRight, dock_id_bottomRight;
        ImGui::DockBuilderSplitNode(dock_id_right, ImGuiDir_Up, 0.8f, &dock_id_topRight, &dock_id_bottomRight);

        ImGuiID dock_id_topLeft, dock_id_bottomLeft;
        ImGui::DockBuilderSplitNode(dock_id_left, ImGuiDir_Up, 0.8f, &dock_id_topLeft, &dock_id_bottomLeft);

        // For defining the position of the dock
        ImGui::DockBuilderDockWindow(m_basicActors->name.c_str(), dock_id_topRight);
        ImGui::DockBuilderDockWindow(m_fileBrowser->name.c_str(), dock_id_bottomLeft);
        ImGui::DockBuilderDockWindow(m_viewport->name.c_str(), dock_id_topLeft);
        ImGui::DockBuilderDockWindow(m_sceneGraph->name.c_str(), dock_id_topRight);
        ImGui::DockBuilderDockWindow(m_debugWindow->name.c_str(), dock_id_bottomRight);

        ImGui::DockBuilderFinish(dockspace_id);
    }
#pragma endregion Create dockspace 

    if (optFullscreen)
    {
        ImGui::PopStyleVar(3);
    }

    UpdateWindows();
}

void EditorUi::EndDockSpace()
{
    ImGui::End();
}

void EditorUi::UpdateWindows()
{
    m_basicActors->Update(m_golemEngine);
    m_fileBrowser->Update(m_golemEngine);
    m_viewport->Update(m_golemEngine);
    m_sceneGraph->Update(m_golemEngine);
    m_debugWindow->Update(m_golemEngine);
}