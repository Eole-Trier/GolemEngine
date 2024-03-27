#pragma once

#include "Viewport/scene.h"
#include "Core/gameobject.h"

#include <GLFW/glfw3.h>
#include "vector2.h"

class Mouse
{
public:
	struct m_leftMouseButton
	{
		bool isPressed = false;
		int x;
		int y;
	};

	std::vector<GameObject*> gameObjects;

public:
	Mouse(const std::vector<GameObject*>& objects);
	~Mouse();

	void mouse_button_callback(int button, int action, int x, int y);
};