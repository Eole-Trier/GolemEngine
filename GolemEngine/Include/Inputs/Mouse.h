#pragma once

#include <GLFW/glfw3.h>
#include "vector2.h"

class Mouse
{
private:
	Vector2 m_coordinates;

public:
	Mouse();
	~Mouse();

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
};