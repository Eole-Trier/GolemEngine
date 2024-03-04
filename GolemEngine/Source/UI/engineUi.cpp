#include "UI/engineUi.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "UI/Windows/basicActors.h"
#include "UI/Windows/viewport.h"
#include "UI/Windows/fileBrowser.h"
#include "UI/Windows/worldActors.h"
#include "UI/Windows/debugWindow.h"
#include "golemEngine.h"
#include <iostream>

EngineUi::EngineUi(GolemEngine* _golemEngine) 
    : 
    m_golemEngine(_golemEngine),
	m_basicActors(new BasicActors()),
	m_viewport(new Viewport()),
	m_fileBrowser(new FileBrowser()),
	m_worldActors(new WorldActors()),
	m_debugWindow(new DebugWindow()) 
{}

EngineUi::~EngineUi() {}

void EngineUi::BeginDockSpace()
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

        ImGui::DockBuilderDockWindow("Basic_Actors", dock_id_bottomRight);
        ImGui::DockBuilderDockWindow("File_Browser", dock_id_topRight);
        ImGui::DockBuilderDockWindow("Viewport", dock_id_topLeft);
        ImGui::DockBuilderDockWindow("World_Actors", dock_id_bottomLeft);
        ImGui::DockBuilderDockWindow("Debug", dock_id_topRight);
        
        ImGui::DockBuilderFinish(dockspace_id);
    }

    if (optFullscreen)
    {
        ImGui::PopStyleVar(3);
    }

    UpdateLoop();
}

void EngineUi::EndDockSpace()
{
    ImGui::End();
}

void EngineUi::UpdateLoop()
{
    
    m_basicActors->Update();
    m_fileBrowser->Update();
    m_viewport->Update(m_golemEngine);
    m_worldActors->Update();
    m_debugWindow->Update(m_golemEngine);
}