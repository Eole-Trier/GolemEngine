#include "editor.h"

#include <GLFW/glfw3.h>

Editor::Editor()
{
	m_golemEngine = new GolemEngine();
}

Editor::~Editor() {}

void Editor::Init()
{
	m_golemEngine->Init();
}

void Editor::Run()
{
	Init();
	MainLoop();
	Cleanup();
}

void Editor::MainLoop()
{
	m_golemEngine->Render();
}

void Editor::Cleanup()
{
	m_golemEngine->Close();
	delete m_golemEngine->GetScene();
	delete m_golemEngine;
}