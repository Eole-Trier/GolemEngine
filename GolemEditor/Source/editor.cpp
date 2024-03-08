#include "editor.h"

#include <GLFW/glfw3.h>


#include "golemEngine.h"
#include "UI/editorUi.h"

Editor::Editor()
	: 
	m_golemEngine(new GolemEngine()),
	m_editorUi(new EditorUi(m_golemEngine))
{}

Editor::~Editor() {}

void Editor::Init()
{
	m_golemEngine->Init();
}

void Editor::MainLoop()
{
	
	m_golemEngine->Update();
	m_editorUi->Update();
	std::cout << "test from editor mainloop" << std::endl;
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