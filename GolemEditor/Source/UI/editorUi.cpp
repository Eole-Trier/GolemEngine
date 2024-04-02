#include "UI/editorUi.h"

#include "golemEngine.h"
#include "UI/Windows/window.h"
#include "Ui/Windows/basicActors.h"
#include "Ui/Windows/viewport.h"
#include "Ui/Windows/fileBrowser.h"
#include "Ui/Windows/sceneGraph.h"
#include "Ui/Windows/debugWindow.h"
#include "UI/Windows/inspector.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "Inputs/inputManager.h"
#include "Wrappers/windowWrapper.h"


void EditorUi::Init()
{
    // Add windows to be used in dockspace later
    m_windows.push_back(new Viewport("Viewport"));
    m_windows.push_back(new BasicActors("Basic_Actors"));
    m_windows.push_back(new FileBrowser("File_Browser"));
    m_windows.push_back(new SceneGraph("Scene_Graph"));
    m_windows.push_back(new DebugWindow("Debug"));
    m_windows.push_back(new Inspector("Inspector"));

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
        style.WindowRounding = 4;
        style.FrameRounding = 4;
        style.GrabRounding = 3;
        style.ScrollbarSize = 7;
        style.ScrollbarRounding = 0;
    }

    ImGui_ImplGlfw_InitForOpenGL(WindowWrapper::window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
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

    ImGui::Begin("DockSpace_Window", &dockspaceOpen, windowFlags);

    m_toolbar->Update();
    
    if (optFullscreen)
    {
        ImGui::PopStyleVar(3);
    }
    
#pragma region Create dockspace

    ImGuiID dockspace_id = ImGui::GetID("DockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspaceFlags);

    // Dock Control Space
    static bool init = true;
        if (init)
        {
            init = false;
            ImGui::DockBuilderRemoveNode(dockspace_id);
            ImGui::DockBuilderAddNode(dockspace_id);
            ImGui::DockBuilderSetNodeSize(dockspace_id, ImGui::GetMainViewport()->Size);

            // Split window from [] to [dock_id_left | dock_id_right]
            ImGuiID dock_id_left, dock_id_right;
            ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.8f, &dock_id_left, &dock_id_right);

            // Split window from [dock_id_left | dock_id_right] to [              | dock_id_topRight    ]
            //                                                     [ dock_id_left |       ---           ]
            //                                                     [              | dock_id_bottomRight ]
            ImGuiID dock_id_topRight, dock_id_bottomRight;
            ImGui::DockBuilderSplitNode(dock_id_right, ImGuiDir_Up, 0.4f, &dock_id_topRight, &dock_id_bottomRight);

            // Split window from [              | dock_id_topRight    ] to [ dock_id_topLeft | dock_id_topRight    ]
            //                   [ dock_id_left |       ---           ]    [        ---      |       ---           ]
            //                   [              | dock_id_bottomRight ]    [ dock_id_bottom  | dock_id_bottomRight ]
            ImGuiID dock_id_topLeft, dock_id_bottom;
            ImGui::DockBuilderSplitNode(dock_id_left, ImGuiDir_Down, 0.3f, &dock_id_bottom, &dock_id_topLeft);

            // Split window from [ dock_id_topLeft | dock_id_topRight    ] to [ dock_id_topLeft | dock_id_middle | dock_id_topRight    ]
            //                   [        ---      |       ---           ]    [                ---               |       ---           ]
            //                   [ dock_id_bottom  | dock_id_bottomRight ]    [            dock_id_bottom        | dock_id_bottomRight ]
            ImGuiID dock_id_middle;
            ImGui::DockBuilderSplitNode(dock_id_topLeft, ImGuiDir_Left, 0.2f, &dock_id_topLeft, &dock_id_middle);


            // For defining the position of the dock
            ImGui::DockBuilderDockWindow(GetWindowByName("Basic_Actors")->name.c_str(), dock_id_topLeft);
            ImGui::DockBuilderDockWindow(GetWindowByName("File_Browser")->name.c_str(), dock_id_bottom);
            ImGui::DockBuilderDockWindow(GetWindowByName("Viewport")->name.c_str(), dock_id_middle);
            ImGui::DockBuilderDockWindow(GetWindowByName("Scene_Graph")->name.c_str(), dock_id_topRight);
            ImGui::DockBuilderDockWindow(GetWindowByName("Debug")->name.c_str(), dock_id_topRight);
            ImGui::DockBuilderDockWindow(GetWindowByName("Inspector")->name.c_str(), dock_id_bottomRight);

            ImGui::DockBuilderFinish(dockspace_id);
        }
#pragma endregion Create dockspace 

    UpdateWindows();
}

void EditorUi::EndDockSpace()
{
    ImGui::End();
}

void EditorUi::UpdateWindows()
{
    for (Window* window : m_windows)
    {
        window->Update();
    }
    ImGuiContext& g = *GImGui;
}

Window* EditorUi::GetWindowByName(std::string _name)
{
    for (Window* window : m_windows)
    {
        if (window->name == _name)
        {
            return window;
        }
    }
    Log::Print("No window with the name %s has been found", _name.c_str());
    return nullptr;
}

Vector2 EditorUi::GetDockedWindowPosition(std::string _dockedWindowName)
{
    ImGuiContext& g = *GImGui;
    Vector2 temp;
    for (int i = 0; i < g.Windows.Size; i++) 
    {
        ImGuiWindow* window = g.Windows[i];
        if (window && window->DockNode && window->DockNode->TabBar && window->DockNode->TabBar->Tabs.Size > 0 && window->DockNode->TabBar->Tabs[0].ID == ImHashStr(_dockedWindowName.c_str()))
        {
            temp = { window->Pos.x, window->Pos.y };
            return temp;
        }
    }
    return { -1, -1 };
}