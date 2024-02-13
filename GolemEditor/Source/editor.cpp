#include "editor.h"

#include <GLFW/glfw3.h>

Editor::Editor() 
{
	m_viewport = new Window("Viewport", 800, 600);
}

Editor::~Editor() {}

void Editor::Init()
{
	m_viewport->Init();
}

void Editor::Run()
{
	Init();
	MainLoop();
	Cleanup();
}

void Editor::MainLoop()
{
	m_viewport->Render();
}

void Editor::Cleanup()
{
	m_viewport->Close();
	delete m_viewport;
}