#include "editor.h"

#include <wtypes.h>

#include "golemEngine.h"
#include "Ui/editorUi.h"
#include "Wrappers/windowWrapper.h"
#include "Wrappers/graphicWrapper.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

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
	WindowWrapper* windowWrapper = WindowWrapper::GetInstance();

    windowWrapper->Init();
    m_window = windowWrapper->NewWindow(m_screenWidth, m_screenHeight, m_name.c_str(), NULL, NULL);
    if (m_window == NULL)
    {
        std::cout << "Failed to create GLFW window : " << m_name << std::endl;
        windowWrapper->Terminate();
    }
    windowWrapper->SetCurrentWindow(m_window);
}

void Editor::InitGraphics()
{
	GraphicWrapper* graphicWrapper = GraphicWrapper::GetInstance();
    if (!graphicWrapper->Init())
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
} 

void Editor::InitUi(GLFWwindow* _window)
{
    m_editorUi->Init(_window);
}

void Editor::Init()
{
    InitWindow();
    InitGraphics();
    InitUi(m_window);
    m_golemEngine->SetWindow(m_window);
    m_golemEngine->Init();
}

void Editor::MainLoop()
{
	ImGuiIO& io = ImGui::GetIO();
	GraphicWrapper* graphicInterface = GraphicWrapper::GetInstance();
	graphicInterface->SetViewport(0, 0, m_screenWidth, m_screenHeight);

	WindowWrapper* windowInterface = WindowWrapper::GetInstance();

	while (!windowInterface->ShouldWindowClose(m_window))
	{
		windowInterface->ProcessEvents();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		m_editorUi->BeginDockSpace();

		m_golemEngine->ProcessInput();
		m_golemEngine->Update();

		m_editorUi->EndDockSpace();

		ImGui::Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = windowInterface->GetCurrentWindow();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			windowInterface->SetCurrentWindow(backup_current_context);
		}

		windowInterface->SwapBuffers(m_window);
	}
}

void Editor::Cleanup() {}

void Editor::Run()
{
	Init();
	MainLoop();
	Cleanup();
}