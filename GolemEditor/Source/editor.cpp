#include "editor.h"

Editor::Editor() {}

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
