#include "editor.h"

#include <iostream>
#include <wtypes.h>
#include <Wrappers/audioWrapper.h>
#include "Components/audio.h"

#include "golemEngine.h"
#include "Ui/editorUi.h"
#include "Wrappers/windowWrapper.h"
#include "Wrappers/graphicWrapper.h"
#include "Inputs/inputManager.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

Editor::Editor()
	:
	m_name("Golem Engine")
{
    // Get screen dimensions
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);

	WindowWrapper::SetScreenSize({ (float)desktop.right, (float)desktop.bottom });
	AudioWrapper::GetInstance().InitDevice();
}

Editor::~Editor() {}

void Editor::InitWindow()
{
	WindowWrapper::InitWindow();
    WindowWrapper::window = WindowWrapper::NewWindow(WindowWrapper::GetScreenSize().x, WindowWrapper::GetScreenSize().y, m_name.c_str(), NULL, NULL);
    if (WindowWrapper::window == NULL)
    {
        std::cout << "Failed to create GLFW window : " << m_name << std::endl;
		WindowWrapper::Terminate();
    }
	WindowWrapper::MakeContext(WindowWrapper::window);
}

void Editor::InitGraphics()
{
    if (!GraphicWrapper::Init())
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
	GraphicWrapper::EnableDepth();
} 

void Editor::InitUi()
{
    EditorUi::Init();
}

void Editor::Init()
{
    InitWindow();
    InitGraphics();
    InitUi();
    GolemEngine::Init();
}

void Editor::MainLoop()
{
	ImGuiIO& io = ImGui::GetIO();
	GraphicWrapper::SetViewport(0, 0, WindowWrapper::GetScreenSize().x, WindowWrapper::GetScreenSize().y);

	while (!WindowWrapper::ShouldWindowClose(WindowWrapper::window))
	{
		WindowWrapper::ProcessEvents();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		EditorUi::BeginDockSpace();

		GolemEngine::ProcessInput();
		GolemEngine::Update();

		EditorUi::EndDockSpace();

		ImGui::Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = WindowWrapper::window;
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			WindowWrapper::MakeContext(backup_current_context);
		}

		WindowWrapper::SwapBuffers(WindowWrapper::window);
		AudioWrapper::GetInstance().UpdatePosition();
	}
}

void Editor::Cleanup()
{
}

void Editor::Run()
{
	Init();
	MainLoop();
	Cleanup();
}