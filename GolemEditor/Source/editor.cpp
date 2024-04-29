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

#include "SystemTable.h"
#include "RuntimeObjectSystem.h"
#include "StdioLogSystem.h"
#include "rccppMainLoop.h"
#include "Resource/tools.h"


static IRuntimeObjectSystem*    g_pRuntimeObjectSystem;
static StdioLogSystem           g_Logger;
static SystemTable              g_SystemTable;

bool RCCppInit()
{
    g_pRuntimeObjectSystem = new RuntimeObjectSystem;
    if (!g_pRuntimeObjectSystem->Initialise(&g_Logger, &g_SystemTable))
    {
        delete g_pRuntimeObjectSystem;
        g_pRuntimeObjectSystem = NULL;
        return false;
    }

    // ensure include directories are set - use location of this file as starting point
    FileSystemUtils::Path basePath = g_pRuntimeObjectSystem->FindFile(__FILE__).ParentPath();
    FileSystemUtils::Path imguiIncludeDir = basePath / "imgui";
    g_pRuntimeObjectSystem->AddIncludeDir(imguiIncludeDir.c_str());
    g_pRuntimeObjectSystem->AddIncludeDir("E:\\Projects\\dev\\2023_gp_2027_gp_2027_projet_moteur-golem\\GolemEngine\\External\\imgui");
    g_pRuntimeObjectSystem->AddIncludeDir("E:\\Projects\\dev\\2023_gp_2027_gp_2027_projet_moteur-golem\\GolemEngine\\External\\imgui\\backends");
    g_pRuntimeObjectSystem->AddIncludeDir("E:\\Projects\\dev\\2023_gp_2027_gp_2027_projet_moteur-golem\\GolemEngine\\Include");
    g_pRuntimeObjectSystem->AddIncludeDir("E:\\Projects\\dev\\2023_gp_2027_gp_2027_projet_moteur-golem\\Libraries\\Include");
    g_pRuntimeObjectSystem->AddIncludeDir("E:\\Projects\\dev\\2023_gp_2027_gp_2027_projet_moteur-golem\\Libraries\\Include\\MathsLib");
    g_pRuntimeObjectSystem->RemoveFromRuntimeFileList("E:\\Projects\\dev\\2023_gp_2027_gp_2027_projet_moteur-golem\\Libraries\\Include\\Refl\\refl.hpp");
    return true;
}

void RCCppUpdate()
{
    //check status of any compile
    if (g_pRuntimeObjectSystem->GetIsCompiledComplete())
    {
        // load module when compile complete
        g_pRuntimeObjectSystem->LoadCompiledModule();
    }

    if (!g_pRuntimeObjectSystem->GetIsCompiling())
    {
        float deltaTime = 1.0f / ImGui::GetIO().Framerate;
        g_pRuntimeObjectSystem->GetFileChangeNotifier()->Update(deltaTime);
    }
}

void RCCppCleanup()
{
    delete g_pRuntimeObjectSystem;
}

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
    RCCppInit();
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
        RCCppUpdate();
        g_SystemTable.pRCCppMainLoopI->MainLoop();
        GolemEngine::GetPlayerCamera()->m_position.z -= g_SystemTable.pRCCppMainLoopI->GetFloat();
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
    RCCppCleanup();
}

void Editor::Run()
{
	Init();
	MainLoop();
	Cleanup();
}