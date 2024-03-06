#pragma once
#include "UI/engineUi.h"

struct GLFWwindow;
class GolemEngine;
class Camera;

class Viewport : Window
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

	void Update(GolemEngine* _golemEngine);

	void MouseCallback(GolemEngine* _golemEngine, double _xposIn, double _yposIn);
	static void ScrollCallback(GLFWwindow* _window, double _xoffset, double _yoffset);

	Camera* GetCamera();
	void MouseMovement(GolemEngine* _golemEngine);


};