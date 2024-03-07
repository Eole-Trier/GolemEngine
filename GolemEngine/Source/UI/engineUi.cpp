#include "UI/engineUi.h"

#include "UI/Windows/basicActors.h"
#include "UI/Windows/viewport.h"
#include "UI/Windows/fileBrowser.h"
#include "UI/Windows/worldActors.h"
#include "UI/Windows/debugWindow.h"
#include "golemEngine.h"
#include <iostream>
#include "Wrappers/interfaceWrapper.h"


EngineUi::EngineUi(GolemEngine* _golemEngine) 
    : 
    m_golemEngine(_golemEngine),
	m_viewport(new Viewport()),
	m_basicActors(new BasicActors()),
	m_fileBrowser(new FileBrowser()),
	m_worldActors(new WorldActors()),
	m_debugWindow(new DebugWindow()) 
{}

EngineUi::~EngineUi() {}

void EngineUi::BeginDockSpace()
{
    InterfaceWrapper::GetInstance()->NewFrameImGui();
    InterfaceWrapper::GetInstance()->EditorStyle();

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
        const ImGuiViewport* viewport = InterfaceWrapper::GetInstance()->GetMainViewport();
        InterfaceWrapper::GetInstance()->SetNextWindowPos(viewport->WorkPos);
        InterfaceWrapper::GetInstance()->SetNextWindowSize(viewport->WorkSize);
        InterfaceWrapper::GetInstance()->SetNextWindowViewport(viewport->ID);
        InterfaceWrapper::GetInstance()->PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        InterfaceWrapper::GetInstance()->PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        InterfaceWrapper::GetInstance()->PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });

        windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;
    }

    InterfaceWrapper::GetInstance()->Begin("DockSpace Demo", &dockspaceOpen, windowFlags);

    GolemID dockspace_id = InterfaceWrapper::GetInstance()->GetID("DockSpace");
    InterfaceWrapper::GetInstance()->DockSpace(dockspace_id, GolemVec2(0.0f, 0.0f), dockspaceFlags);

    static bool init = true;
    if (init)
    {
        GolemID dock_id_left, dock_id_right;
        init = false;
        InterfaceWrapper::GetInstance()->DockBuilderAddNode(dockspace_id);
        InterfaceWrapper::GetInstance()->DockBuilderSetNodeSize(dockspace_id, ImGui::GetMainViewport()->Size);

        InterfaceWrapper::GetInstance()->DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.8f, &dock_id_left, &dock_id_right);

        GolemID dock_id_topRight, dock_id_bottomRight;
        InterfaceWrapper::GetInstance()->DockBuilderSplitNode(dock_id_right, ImGuiDir_Up, 0.8f, &dock_id_topRight, &dock_id_bottomRight);

        GolemID dock_id_topLeft, dock_id_bottomLeft;
        InterfaceWrapper::GetInstance()->DockBuilderSplitNode(dock_id_left, ImGuiDir_Up, 0.8f, &dock_id_topLeft, &dock_id_bottomLeft);

        InterfaceWrapper::GetInstance()->DockBuilderDockWindow("Basic_Actors", dock_id_topRight);
        InterfaceWrapper::GetInstance()->DockBuilderDockWindow("File_Browser", dock_id_bottomLeft);
        InterfaceWrapper::GetInstance()->DockBuilderDockWindow("Viewport", dock_id_topLeft);
        InterfaceWrapper::GetInstance()->DockBuilderDockWindow("World_Actors", dock_id_topRight);
        InterfaceWrapper::GetInstance()->DockBuilderDockWindow("Debug", dock_id_bottomRight);

        InterfaceWrapper::GetInstance()->DockBuilderFinish(dockspace_id);
    }

    if (optFullscreen)
    {
        InterfaceWrapper::GetInstance()->PopStyleVar(3);
    }
    InterfaceWrapper::GetInstance()->End();

    UpdateLoop();
}

void EngineUi::UpdateLoop()
{
    m_basicActors->Update();
    m_fileBrowser->Update();
    m_worldActors->Update();
    m_viewport->Update(m_golemEngine);
    m_debugWindow->Update(m_golemEngine);

    Camera* camera = Camera::instance;

    InterfaceWrapper::GetInstance()->Begin("Camera");
    InterfaceWrapper::GetInstance()->SliderFloat("Camera Move Speed", &camera->movementSpeed, camera->minSpeed, camera->maxSpeed, 0);
    InterfaceWrapper::GetInstance()->End();
}

bool EngineUi::GetIsFullscreen()
{
    return m_isFullscreen;
}

void EngineUi::SetIsFullscreen(bool _value)
{
    m_isFullscreen = _value;
}
void EngineUi::SetViewport(int _width, int _height)
{
    m_viewport->width = _width;
    m_viewport->height = _height;
}

Viewport* EngineUi::GetViewport()
{
    return m_viewport;
}
