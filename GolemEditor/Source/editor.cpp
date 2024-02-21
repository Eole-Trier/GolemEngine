#include "editor.h"

#include <GLFW/glfw3.h>

Editor::Editor()
{
	m_scene = new Scene();
	m_engineWindow = new EngineWindow("Golem Engine");
	m_engineWindow->scene = m_scene;
}

Editor::~Editor() {}

void Editor::Init()
{
	m_engineWindow->Init();
}

void Editor::Run()
{
	Init();
	MainLoop();
	Cleanup();
}

void Editor::MainLoop()
{
	m_engineWindow->Render();
}

void Editor::Cleanup()
{
	m_engineWindow->Close();
	delete m_engineWindow;
	delete m_scene;
}