#include "editor.h"

#include <iostream>
#include <wtypes.h>
#include <Wrappers/audioWrapper.h>
#include "Components/audio.h"

#include "golemEngine.h"
#include "Components/transform.h"
#include "Ui/editorUi.h"
#include "Wrappers/windowWrapper.h"
#include "Wrappers/graphicWrapper.h"
#include "Inputs/inputManager.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "ImGuizmo.h"
#include "MathsLib/utils.h"
#include <thread>

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/class.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/mono-config.h>

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

MonoDomain* domain;

void Mono()
{
	mono_set_assemblies_path("C:\\Program Files\\Mono\\lib");
	domain = mono_jit_init("a");
}

void Editor::MainLoop()
{
	Mono();
	ImGuiIO& io = ImGui::GetIO();
	GraphicWrapper::SetViewport(0, 0, WindowWrapper::GetScreenSize().x, WindowWrapper::GetScreenSize().y);

	while (!WindowWrapper::ShouldWindowClose(WindowWrapper::window))
	{
		const char* managed_binary_path = "C:\\dev\\2023_gp_2027_gp_2027_projet_moteur-golem\\GolemEditor\\Scripts\\Test.dll";
		MonoAssembly* assembly = mono_domain_assembly_open(domain, managed_binary_path);
		MonoImage* image = mono_assembly_get_image(assembly);
		MonoClass* main_class = mono_class_from_name(image, "MonoCsharp", "MainTest");

		MonoMethodDesc* entry_point_method_desc = mono_method_desc_new("MonoCsharp.MainTest:Main()", true);
		MonoMethod* entry_point_method = mono_method_desc_search_in_class(entry_point_method_desc, main_class);
		mono_method_desc_free(entry_point_method_desc);
		mono_runtime_invoke(entry_point_method, NULL, NULL, NULL);
		//mono_jit_cleanup(domain);

		WindowWrapper::ProcessEvents();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGuizmo::BeginFrame();

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
	ImGui::EndFrame();
}

void Editor::Run()
{
	Init();
	MainLoop();
	Cleanup();
}