#pragma once

#include "Viewport/camera.h"

class GolemEngine;

class Viewport
{
private:
	static Camera* m_camera;
	double m_cursorX;
	double m_cursorY;
	float m_lastX;
	float m_lastY;
	float m_yaw;
	float m_pitch;
	bool m_firstMouse;

public:
	int width, height;

public:

	Viewport();
	~Viewport();

	void Update(GolemEngine* _golemEngine, const char* _name = "default_window");

	void MouseCallback(GolemEngine* _golemEngine, double _xposIn, double _yposIn);
	static void ScrollCallback(GLFWwindow* _window, double _xoffset, double _yoffset);

	Camera* GetCamera();
	void MouseMovement(GolemEngine* _golemEngine);
};