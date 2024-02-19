#pragma once

#include <string>
#include "dll.h"
class Scene;
struct GLFWwindow;

class GOLEM_ENGINE_API Window
{
private:
	GLFWwindow* m_window = nullptr;
	std::string m_name;

public:
	unsigned int width = 800;
	unsigned int height = 600;

public:
	Window();
	~Window();
	Window(const char* _name, unsigned int _width, unsigned int _height);

	GLFWwindow* GetWindow();

	void Init();
	void Render(Scene* _scene);
	void Close();

	void ImGuiInit();
	void ImGuiLoop();
	void ImGuiClean();

	void ProcessInput();
};