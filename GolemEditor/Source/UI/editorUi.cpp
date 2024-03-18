#include "UI/editorUi.h"

#include "golemEngine.h"
#include "UI/Windows/window.h"
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
    m_golemEngine(_golemEngine)
{
    m_windows.push_back(new Viewport("Viewport"));
    m_windows.push_back(new BasicActors("Basic_Actors"));
    m_windows.push_back(new FileBrowser("File_Browser"));
    m_windows.push_back(new SceneGraph("Scene_Graph"));
    m_windows.push_back(new DebugWindow("Debug"));
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
        ImGui::DockBuilderDockWindow(GetWindowByName("Basic_Actors")->name.c_str(), dock_id_topRight);
        ImGui::DockBuilderDockWindow(GetWindowByName("File_Browser")->name.c_str(), dock_id_bottomLeft);
        ImGui::DockBuilderDockWindow(GetWindowByName("Viewport")->name.c_str(), dock_id_topLeft);
        ImGui::DockBuilderDockWindow(GetWindowByName("Scene_Graph")->name.c_str(), dock_id_topRight);
        ImGui::DockBuilderDockWindow(GetWindowByName("Debug")->name.c_str(), dock_id_bottomRight);

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
    ImGui::Begin("My Window", NULL, ImGuiWindowFlags_NoCollapse);
    if (ImGui::IsMouseHoveringRect(ImGui::GetWindowPos(), ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowSize().x, ImGui::GetWindowPos().y + ImGui::GetWindowSize().y)))
    {
        std::cout << "In this window" << std::endl;
    }
    else
        std::cout << "Out of window" << std::endl;
    ImGui::End();
}

void EditorUi::UpdateWindows()
{
    for (Window* window : m_windows)
    {
        window->Update(m_golemEngine);
    }
}

Window* EditorUi::GetWindowByName(std::string _name)
{
    for (Window* window : m_windows)
    {
        if (window->name == _name)
            return window;
    }
    Log::Print("No window with the name %s has been found", _name.c_str());
    return nullptr;
}
