#pragma once

#include "Viewport/camera.h"
#include "UI/Windows/window.h"

class GolemEngine;

class Viewport : public Window
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
	int width = 0, height = 0;

public:

	Viewport(std::string _name);
	~Viewport();

	void Update(GolemEngine* _golemEngine) override;

	void MouseCallback(GolemEngine* _golemEngine, double _xposIn, double _yposIn);
	static void ScrollCallback(GLFWwindow* _window, double _xoffset, double _yoffset);

	Camera* GetCamera();
	void MouseMovement(GolemEngine* _golemEngine);
};