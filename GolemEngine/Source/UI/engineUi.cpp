#include "UI/engineUi.h"

#include "UI/Windows/basicActors.h"
#include "UI/Windows/viewport.h"
#include "UI/Windows/fileBrowser.h"
#include "UI/Windows/worldActors.h"
#include "UI/Windows/debugWindow.h"
#include "golemEngine.h"
#include <iostream>
#include <vector>
#include "Wrappers/interfaceWrapper.h"


EngineUi::EngineUi(GolemEngine* _golemEngine) 
    : 
    m_golemEngine(_golemEngine),
	m_viewport(new Viewport()),
	m_basicActors(new BasicActors()),
	m_fileBrowser(new FileBrowser()),
	m_worldActors(new WorldActors()),
	m_debugWindow(new DebugWindow()) 
{
    m_windowList.push_back(m_viewport);
    m_windowList.push_back(m_basicActors);
    m_windowList.push_back(m_fileBrowser);
    m_windowList.push_back(m_worldActors);
    m_windowList.push_back(m_debugWindow);
}

EngineUi::~EngineUi() {}

void EngineUi::InitUI(GLFWwindow* _window)
{
    GOLEM_UI->Init(_window);
}

void EngineUi::Update()
{
    GOLEM_UI->NewFrameImGui();
    GOLEM_UI->EditorStyle();

    //Dock Space
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
        const ImGuiViewport* viewport = GOLEM_UI->GetMainViewport();
        GOLEM_UI->SetNextWindowPos(viewport->WorkPos);
        GOLEM_UI->SetNextWindowSize(viewport->WorkSize);
        GOLEM_UI->SetNextWindowViewport(viewport->ID);
        GOLEM_UI->PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        GOLEM_UI->PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        GOLEM_UI->PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });

        windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;
    }

    GOLEM_UI->Begin("DockSpace Demo", &dockspaceOpen, windowFlags);

    GolemID dockspace_id = GOLEM_UI->GetID("DockSpace");
    GOLEM_UI->DockSpace(dockspace_id, GolemVec2(0.0f, 0.0f), dockspaceFlags);

    // Dock Conctrol Space
    static bool init = true;
    if (init)
    {
        // The dock has a default 4 block layout
        // Topleft     TopRight
        // Bottomlefr  BottomRight
        GolemID dock_id_left, dock_id_right;
        init = false;
        GOLEM_UI->DockBuilderAddNode(dockspace_id);
        GOLEM_UI->DockBuilderSetNodeSize(dockspace_id, ImGui::GetMainViewport()->Size);

        GOLEM_UI->DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.8f, &dock_id_left, &dock_id_right);

        GolemID dock_id_topRight, dock_id_bottomRight;
        GOLEM_UI->DockBuilderSplitNode(dock_id_right, ImGuiDir_Up, 0.8f, &dock_id_topRight, &dock_id_bottomRight);

        GolemID dock_id_topLeft, dock_id_bottomLeft;
        GOLEM_UI->DockBuilderSplitNode(dock_id_left, ImGuiDir_Up, 0.8f, &dock_id_topLeft, &dock_id_bottomLeft);

        // For defining the position of the dock
        GOLEM_UI->DockBuilderDockWindow("Basic_Actors", dock_id_topRight);
        GOLEM_UI->DockBuilderDockWindow("File_Browser", dock_id_bottomLeft);
        GOLEM_UI->DockBuilderDockWindow("Viewport", dock_id_topLeft);
        GOLEM_UI->DockBuilderDockWindow("World_Actors", dock_id_topRight);
        GOLEM_UI->DockBuilderDockWindow("Debug", dock_id_bottomRight);

        GOLEM_UI->DockBuilderFinish(dockspace_id);
    }

    if (optFullscreen)
    {
        GOLEM_UI->PopStyleVar(3);
    }
    GOLEM_UI->End();

    CustomWindows();

    GOLEM_UI->Render();
}

void EngineUi::CustomWindows()
{
    for (auto dock : m_windowList)
    {
        if(dock->isRendered)
            dock->Update(m_golemEngine);
    }

    Camera* camera = Camera::instance;

    GOLEM_UI->Begin("Menu");
    
    if (GOLEM_UI->Button("New Window"))
    {
        Window* newWindow = new Window();
        AddNewWindow(newWindow);
    }
    GOLEM_UI->SameLine();
    if (GOLEM_UI->Button("Show All Windows"))
    {
        for (auto dock : m_windowList)
        {
            dock->isRendered = true;
        }
    }
    GOLEM_UI->SameLine();
    if (GOLEM_UI->Button("Hide All Windows"))
    {
        for (auto dock : m_windowList)
        {
            dock->isRendered = false;
        }
    }

    GOLEM_UI->End();
}

bool EngineUi::GetIsFullscreen()
{
    return m_isFullscreen;
}

void EngineUi::SetIsFullscreen(bool _value)
{
    m_isFullscreen = _value;
}

Viewport* EngineUi::GetViewport()
{
    return m_viewport;
}

void EngineUi::AddNewWindow(Window* _newWindow)
{
    m_windowList.push_back(_newWindow);
}

void Window::Update(GolemEngine* _golemEngine, const char* _name)
{
    GOLEM_UI->Begin(_name);
    GOLEM_UI->End();
}
