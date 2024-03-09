#include "editor.h"

#include <GLFW/glfw3.h>
#include <wtypes.h>

#include "golemEngine.h"
#include "UI/editorUi.h"
#include "Wrappers/interfaceWrapper.h"
#include "Wrappers/windowWrapper.h"
#include "Wrappers/graphicWrapper.h"

Editor::Editor()
	: 
    m_name("Golem Engine"),
    m_golemEngine(new GolemEngine()),
    m_editorUi(new EditorUi(m_golemEngine))
{
    // Get screen dimensions
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    m_screenWidth = desktop.right;
    m_screenHeight = desktop.bottom;

    m_golemEngine->SetScreenSize(m_screenWidth, m_screenHeight);
}

Editor::~Editor() {}

void Editor::InitWindow()
{
    WINDOW_INTERFACE->Init();
    WINDOW_INTERFACE->SetOption(OPENGL_MAJOR_VERSION, 3);
    WINDOW_INTERFACE->SetOption(OPENGL_MINOR_VERSION, 0);

    // Create window
    m_window = WINDOW_INTERFACE->NewWindow(m_screenWidth, m_screenHeight, m_name.c_str(), NULL, NULL);
    if (m_window == NULL)
    {
        std::cout << "Failed to create GLFW window : " << m_name << std::endl;
        WINDOW_INTERFACE->Terminate();
    }

    WINDOW_INTERFACE->SetCurrentWindow(m_window);

    // Initialize GLAD
    if (!GRAPHIC_INTERFACE->Init())

    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    UI_INTERFACE->Init(m_window);
}

void Editor::Init()
{
    InitWindow();
    m_golemEngine->Init();
}

void Editor::MainLoop()
{
    while (!WINDOW_INTERFACE->ShouldWindowClose(m_golemEngine->GetWindow()))
    {
		m_golemEngine->Update();
        m_editorUi->Update();
        WINDOW_INTERFACE->SwapBuffers(m_golemEngine->GetWindow());
    }
	std::cout << "test from editor mainloop" << std::endl;
}

void Editor::Cleanup()
{
	m_golemEngine->Close();
	delete m_golemEngine->GetScene();
	delete m_golemEngine;
}

void Editor::Run()
{
	Init();
	MainLoop();
	Cleanup();
}