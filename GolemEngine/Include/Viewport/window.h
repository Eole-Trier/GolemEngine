#pragma once
#include "dll.h"

#include <string>

struct GLFWwindow;

class GOLEM_ENGINE_API Window
{
private:
	GLFWwindow* m_window = nullptr;
	std::string m_name;

public:
	unsigned int width = 1800;
	unsigned int height = 1600;

public:
	Window();
	~Window();
	Window(std::string _name, unsigned int _width, unsigned int _height);

	void Init();
	void Render();
	void Close();

	void ProcessInput();
};