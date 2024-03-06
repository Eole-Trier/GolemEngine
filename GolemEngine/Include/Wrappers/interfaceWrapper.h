#pragma once
#include "dll.h"
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GOLEM_ENGINE_API InterfaceWrapper
{
public:
	static InterfaceWrapper* GetInstance();

	void Init(GLFWwindow* _window);
	void NewFrameImGui();

public:
	void Begin(const char* _name);

	void Dock();
	void Loop();
	void EditorStyle();

	void End();

	void Render();
private:
	InterfaceWrapper();
	~InterfaceWrapper();

	static InterfaceWrapper* m_instancePtr;

	InterfaceWrapper(const InterfaceWrapper& imGuiWrapper) = delete;
	const InterfaceWrapper& operator=(const InterfaceWrapper& imGuiWrapper) = delete;
};