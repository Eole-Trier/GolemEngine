#include "UI/editorUi.h"

#include "golemEngine.h"
#include "UI/Windows/basicActors.h"
#include "UI/Windows/viewport.h"
#include "UI/Windows/fileBrowser.h"
#include "UI/Windows/worldActors.h"
#include "UI/Windows/debugWindow.h"


EditorUi::EditorUi(GolemEngine* _golemEngine)
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

void EditorUi::Init(GLFWwindow* _window)
{
	
}

void EditorUi::Update()
{

}

void EditorUi::CustomWindow()
{

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