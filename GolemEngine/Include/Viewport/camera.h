#pragma once

#include "dll.h"
#include "vector2.h"
#include "vector3.h"
#include "matrix4.h"


class GOLEM_ENGINE_API Camera
{
private:
	Vector3 m_front;
	Vector3 m_up;
	Vector3 m_right;
	Vector3 m_worldUp;
	float m_yaw;
	float m_pitch;
	float m_movementSpeed;
	float m_mouseSensitivity;
	float m_zoom;
	float m_near;
	float m_far;
	float m_minSpeed;
	float m_maxSpeed;

	Vector2 m_lastMousePos = { 0, 0 };

public:
	Vector3 m_position;
	bool isFirstMouse = true;

public:
	Camera(Vector3 _position = Vector3(0.0f, 0.0f, 3.0f), Vector3 _up = Vector3(0.0f, 1.0f, 0.0f), float _yaw = -90.0f, float _pitch = 0.0f);

	void ProcessKeyboardInput(float _deltaTime);
	void ProcessMouseInput();
	// Process changes on mouse position
	void ProcessMouseMovement(Vector2 _mousePos, bool _constrainPitch);
	// When mouse values changes, process these changes to move the mouse
	void UpdateVectors();
	// Process changes on mouse scrool
	void ProcessMouseScroll(float _yOffset);

	Matrix4 GetViewMatrix();
	float GetZoom();
	float GetNear();
	float GetFar();
};