#pragma once
#include "dll.h"
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GOLEM_ENGINE_API ImGuiWrapper
{
public:
	static ImGuiWrapper& GetInstance();

	void InitImGui(GLFWwindow* _window);
	void NewFrameImGui();

public:
	void EditorStyle();
	void CustomRendrering();

	void LoopImGui();
	
private:
	ImGuiWrapper();
	~ImGuiWrapper();

	ImGuiWrapper(const ImGuiWrapper& imGuiWrapper) = delete;
	const ImGuiWrapper& operator=(const ImGuiWrapper& imGuiWrapper) = delete;
};