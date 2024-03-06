#include "UI/engineUi.h"

#include "imgui.h"
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
    InterfaceWrapper::GetInstance()->Dock();

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
    m_worldActors->Update();
    m_viewport->Update(m_golemEngine);
    m_debugWindow->Update(m_golemEngine);
}