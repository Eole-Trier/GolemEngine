#pragma once

#include "Viewport/camera.h"
#include "UI/Windows/window.h"


class Camera;
class GolemEngine;

class Viewport : public Window
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

	Viewport(std::string _name);
	~Viewport();

	void Update(GolemEngine* _golemEngine) override;

	void SetCamera(Camera* _camera);

	Camera* GetCamera();
};