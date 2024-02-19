#include "editor.h"
#include "Viewport/scene.h"
#include <GLFW/glfw3.h>

Editor::Editor() 
{
	m_window = new Window("Viewport", 800, 600);
	m_scene = new Scene();
}

Editor::~Editor() {}

void Editor::Init()
{
	m_window->Init();
}

void Editor::Run()
{
	Init();
	MainLoop();
	Cleanup();
}

void Editor::MainLoop()
{
	m_window->Render(m_scene);
}

void Editor::Cleanup()
{
	m_window->Close();
	delete m_window;
	delete m_scene;
}