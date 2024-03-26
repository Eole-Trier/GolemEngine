#pragma once

#include "Viewport/scene.h"
#include "Core/gameobject.h"

#include <GLFW/glfw3.h>
#include "vector2.h"

class Mouse
{
public:
	std::vector<GameObject*> gameObjects;

private:
	Vector2 m_coordinates;

public:
	Mouse(const std::vector<GameObject*>& objects);
	~Mouse();

	void mouse_button_callback(GLFWwindow* window, int button, int action);
};