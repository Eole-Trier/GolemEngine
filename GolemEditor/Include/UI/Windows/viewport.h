#pragma once

//#include "Viewport/camera.h"


class Camera;
class GolemEngine;

class Viewport
{
private:
	Camera* m_camera = nullptr;
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

	Viewport();
	~Viewport();

	void Update(GolemEngine* _golemEngine, Camera* _camera, const char* _name = "default_window");
	
	void SetCamera(Camera* _camera);

	Camera* GetCamera();
};