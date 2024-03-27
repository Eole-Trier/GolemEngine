#include "editor.h"

#include <iostream>
#include <wtypes.h>

#include "golemEngine.h"
#include "Ui/editorUi.h"
#include "Wrappers/windowWrapper.h"
#include "Wrappers/graphicWrapper.h"
#include "Inputs/inputManager.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "Resource/tools.h"
#include "SFML/Audio.hpp"

Editor::Editor()
	:
	m_name("Golem Engine"),
	m_golemEngine(GolemEngine::GetInstance())
{
    // Get screen dimensions
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);

	WindowWrapper::SetScreenSize({ (float)desktop.right, (float)desktop.bottom });
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
    EditorUi::Init(m_golemEngine);
}

void Editor::Init()
{
    InitWindow();
    InitGraphics();
    InitUi();
    m_golemEngine->Init();
}

void Editor::MainLoop()
{
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile(Tools::FindFile("music_01.wav")))
	{
	}
	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.setLoop(true);
	sound.play();
	sf::Listener::setPosition(0, 0, 0);
	sf::Vector3f listenerVelocity(0, 0, 1);

	ImGuiIO& io = ImGui::GetIO();
	GraphicWrapper::SetViewport(0, 0, WindowWrapper::GetScreenSize().x, WindowWrapper::GetScreenSize().y);

	while (!WindowWrapper::ShouldWindowClose(WindowWrapper::window))
	{
		WindowWrapper::ProcessEvents();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		EditorUi::BeginDockSpace();

		m_golemEngine->ProcessInput();
		m_golemEngine->Update();

		// Doing 3D sound
		sf::Vector3f listenerPosition = sf::Listener::getPosition();
		sf::Listener::setPosition(listenerPosition + listenerVelocity);
		sf::Vector3f soundPosition = sound.getPosition();
		sf::Vector3f distance = soundPosition - listenerPosition;
		float distanceMagnitude = std::sqrt(distance.x * distance.x + distance.y * distance.y + distance.z * distance.z);
		float attenuationFactor = 1.0f / (1.0f + 0.1f * distanceMagnitude);
		sound.setVolume(100 * attenuationFactor);

		EditorUi::EndDockSpace();

		ImGui::Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags && ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = WindowWrapper::window;
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			WindowWrapper::MakeContext(backup_current_context);
		}

		WindowWrapper::SwapBuffers(WindowWrapper::window);
	}
}

void Editor::Cleanup() 
{
	delete m_golemEngine;
}

void Editor::Run()
{
	Init();
	MainLoop();
	Cleanup();
}