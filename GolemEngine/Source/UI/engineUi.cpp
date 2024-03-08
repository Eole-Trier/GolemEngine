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
    UI_INTERFACE->Init(_window);
}

void EngineUi::Update()
{
    UI_INTERFACE->NewFrameImGui();
    UI_INTERFACE->EditorStyle();

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
        const ImGuiViewport* viewport = UI_INTERFACE->GetMainViewport();
        UI_INTERFACE->SetNextWindowPos(viewport->WorkPos);
        UI_INTERFACE->SetNextWindowSize(viewport->WorkSize);
        UI_INTERFACE->SetNextWindowViewport(viewport->ID);
        UI_INTERFACE->PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        UI_INTERFACE->PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        UI_INTERFACE->PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });

        windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;
    }

    UI_INTERFACE->Begin("DockSpace Demo", &dockspaceOpen, windowFlags);

    GolemID dockspace_id = UI_INTERFACE->GetID("DockSpace");
    UI_INTERFACE->DockSpace(dockspace_id, GolemVec2(0.0f, 0.0f), dockspaceFlags);

    // Dock Conctrol Space
    static bool init = true;
    if (init)
    {
        // The dock has a default 4 block layout
        // Topleft     TopRight
        // Bottomlefr  BottomRight
        GolemID dock_id_left, dock_id_right;
        init = false;
        UI_INTERFACE->DockBuilderAddNode(dockspace_id);
        UI_INTERFACE->DockBuilderSetNodeSize(dockspace_id, ImGui::GetMainViewport()->Size);

        UI_INTERFACE->DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.8f, &dock_id_left, &dock_id_right);

        GolemID dock_id_topRight, dock_id_bottomRight;
        UI_INTERFACE->DockBuilderSplitNode(dock_id_right, ImGuiDir_Up, 0.8f, &dock_id_topRight, &dock_id_bottomRight);

        GolemID dock_id_topLeft, dock_id_bottomLeft;
        UI_INTERFACE->DockBuilderSplitNode(dock_id_left, ImGuiDir_Up, 0.8f, &dock_id_topLeft, &dock_id_bottomLeft);

        // For defining the position of the dock
        UI_INTERFACE->DockBuilderDockWindow("Basic_Actors", dock_id_topRight);
        UI_INTERFACE->DockBuilderDockWindow("File_Browser", dock_id_bottomLeft);
        UI_INTERFACE->DockBuilderDockWindow("Viewport", dock_id_topLeft);
        UI_INTERFACE->DockBuilderDockWindow("World_Actors", dock_id_topRight);
        UI_INTERFACE->DockBuilderDockWindow("Debug", dock_id_bottomRight);

        UI_INTERFACE->DockBuilderFinish(dockspace_id);
    }

    if (optFullscreen)
    {
        UI_INTERFACE->PopStyleVar(3);
    }
    UI_INTERFACE->End();

    CustomWindows();

    UI_INTERFACE->Render();
}

void EngineUi::CustomWindows()
{
    for (auto dock : m_windowList)
    {
        if(dock->isRendered)
            dock->Update(m_golemEngine);
    }

    Camera* camera = Camera::instance;

    UI_INTERFACE->Begin("Menu");
    
    if (UI_INTERFACE->Button("New Window"))
    {
        Window* newWindow = new Window();
        AddNewWindow(newWindow);
    }
    UI_INTERFACE->SameLine();
    if (UI_INTERFACE->Button("Show All Windows"))
    {
        for (auto dock : m_windowList)
        {
            dock->isRendered = true;
        }
    }
    UI_INTERFACE->SameLine();
    if (UI_INTERFACE->Button("Hide All Windows"))
    {
        for (auto dock : m_windowList)
        {
            dock->isRendered = false;
        }
    }

    UI_INTERFACE->End();
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
    UI_INTERFACE->Begin(_name);
    UI_INTERFACE->End();
}
