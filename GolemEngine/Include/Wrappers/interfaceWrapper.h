#pragma once
#include "dll.h"
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GOLEM_ENGINE_API InterfaceWrapper
{
public:
	static InterfaceWrapper* GetInstance();

	void InitImGui(GLFWwindow* _window);
	void NewFrameImGui();

public:
	void Dock();
	void LoopImGui();
	void EditorStyle();

private:
	InterfaceWrapper();
	~InterfaceWrapper();

	static InterfaceWrapper* m_instancePtr;

	InterfaceWrapper(const InterfaceWrapper& imGuiWrapper) = delete;
	const InterfaceWrapper& operator=(const InterfaceWrapper& imGuiWrapper) = delete;
};