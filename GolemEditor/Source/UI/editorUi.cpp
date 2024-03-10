#include "UI/editorUi.h"

#include "golemEngine.h"
#include "UI/Windows/basicActors.h"
#include "UI/Windows/viewport.h"
#include "UI/Windows/fileBrowser.h"
#include "UI/Windows/worldActors.h"
#include "UI/Windows/debugWindow.h"
#include "Wrappers/interfaceWrapper.h"


EditorUi::EditorUi(GolemEngine* _golemEngine)
    :
    m_golemEngine(_golemEngine),
    m_viewport(new Viewport()),
    m_basicActors(new BasicActors()),
    m_fileBrowser(new FileBrowser()),
    m_worldActors(new WorldActors()),
    m_debugWindow(new DebugWindow())
{}

void EditorUi::Init(GLFWwindow* _window)
{
    UI_INTERFACE->Init(_window);
    UI_INTERFACE->EditorStyle();
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
#pragma endregion Setup dockspace

#pragma region Create dockspace
    UI_INTERFACE->Begin("DockSpace Demo", &dockspaceOpen, windowFlags);

    GolemID dockspace_id = UI_INTERFACE->GetID("DockSpace");
    UI_INTERFACE->DockSpace(dockspace_id, GolemVec2(0.0f, 0.0f), dockspaceFlags);

    // Dock Control Space
    static bool init = true;
    if (init)
    {
        // The dock has a default 4 block layout
        // Topleft     TopRight
        // Bottomlefr  BottomRight
        GolemID dock_id_left, dock_id_right;
        init = false;
        UI_INTERFACE->DockBuilderRemoveNode(dockspace_id);
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
#pragma endregion Create dockspace 

    if (optFullscreen)
    {
        UI_INTERFACE->PopStyleVar(3);
    }

    UpdateWindows();
}

void EditorUi::EndDockSpace()
{
    UI_INTERFACE->End();
}

void EditorUi::UpdateWindows()
{
    m_basicActors->Update(m_golemEngine);
    m_fileBrowser->Update(m_golemEngine);
    m_viewport->Update(m_golemEngine);
    m_worldActors->Update(m_golemEngine);
    m_debugWindow->Update(m_golemEngine);
}

bool EditorUi::GetIsFullscreen()
{
    return m_isFullscreen;
}

void EditorUi::SetIsFullscreen(bool _value)
{
    m_isFullscreen = _value;
}

Viewport* EditorUi::GetViewport()
{
    return m_viewport;
}