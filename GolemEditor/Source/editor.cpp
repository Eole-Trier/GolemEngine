#include "editor.h"

#include <GLFW/glfw3.h>

#include "golemEngine.h"

Editor::Editor()
	: m_golemEngine(new GolemEngine()) {}

Editor::~Editor() {}

void Editor::Init()
{
	m_golemEngine->Init();
}

void Editor::MainLoop()
{
	m_golemEngine->Update();
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