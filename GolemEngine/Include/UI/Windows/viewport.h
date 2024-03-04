#pragma once

#include "Viewport/scene.h"

struct GLFWindow;
class GolemEngine;

class Viewport
{
private:
	static float m_lastX;
	static float m_lastY;
	static float m_yaw;
	static float m_pitch;
	static bool m_firstMouse;

public:
	int width, height;

public:
	Viewport(GolemEngine* _golemEngine);
	~Viewport();

	void Init();
	void Update(GolemEngine* _golemEngine);

	static void ResizeCallback(GLFWwindow* window, int _width, int _height);
	static void MouseCallback(GLFWwindow* _window, double _xposIn, double _yposIn);
	static void ScrollCallback(GLFWwindow* _window, double _xoffset, double _yoffset);

};