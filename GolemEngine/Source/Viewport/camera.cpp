#include "Viewport/camera.h"

#include "Wrappers/windowWrapper.h" 
#include "inputManager.h"
#include "utils.h"


Camera::Camera(GLFWwindow* _window, Vector3 _position, Vector3 _up, float _yaw, float _pitch)
	:
	m_window(_window),
	m_position(_position),
	m_front(Vector3(0.0f, 0.0f, -1.0f)),
	m_worldUp(_up),
	m_yaw(_yaw),
	m_pitch(_pitch),
	m_movementSpeed(2.5f),
	m_mouseSensitivity(0.1f),
	m_zoom(45.0f),
    m_near(0.1f),
    m_far(1000.0f)
{
	UpdateVectors();
}

void Camera::ProcessKeyboardInput(float _deltaTime)
{
    if (InputManager::IsKeyPressed(KEY_W))
    {
        m_position += m_front * m_movementSpeed * _deltaTime;
    }
    if (InputManager::IsKeyPressed(KEY_S))
    {
        m_position -= m_front * m_movementSpeed * _deltaTime;
    }
    if (InputManager::IsKeyPressed(KEY_A))
    {
        m_position -= m_right * m_movementSpeed * _deltaTime;
    }
    if (InputManager::IsKeyPressed(KEY_D))
    {
        m_position += m_right * m_movementSpeed * _deltaTime;
    }
    if (InputManager::IsKeyPressed(KEY_Q))
    {
        m_position += m_up * m_movementSpeed * _deltaTime;
    }
    if (InputManager::IsKeyPressed(KEY_E))
    {
        m_position -= m_up * m_movementSpeed * _deltaTime;
    }
}

void Camera::ProcessMouseInput(float _xOffset, float _yOffset, bool _constrainPitch)
{
    _xOffset *= m_mouseSensitivity;
    _yOffset *= m_mouseSensitivity;

    m_yaw += _xOffset;
    m_pitch += _yOffset;

    if (_constrainPitch) {
        if (m_pitch > 89.0f)
            m_pitch = 89.0f;
        if (m_pitch < -89.0f)
            m_pitch = -89.0f;
    }

    UpdateVectors();
}

void Camera::ProcessMouseScroll(float _yOffset)
{
    if (m_movementSpeed + _yOffset > m_maxSpeed || m_movementSpeed + _yOffset < m_minSpeed)
    {
        return;
    }
    m_movementSpeed += (float)_yOffset;
}

void Camera::UpdateVectors()
{
    m_front.x = cos(DegToRad(m_yaw)) * cos(DegToRad(m_pitch));
    m_front.y = sin(DegToRad(m_pitch));
    m_front.z = sin(DegToRad(m_yaw)) * cos(DegToRad(m_pitch));
    m_front = m_front.Normalize();
    m_right = Vector3::Cross(m_front, m_worldUp).Normalize();
    m_up = Vector3::Cross(m_right, m_front).Normalize();
}

Matrix4 Camera::GetViewMatrix()
{
    return Matrix4::LookAt(m_position, m_position + m_front, m_up);
}

float Camera::GetZoom()
{
    return m_zoom;
}

float Camera::GetNear()
{
    return m_near;
}

float Camera::GetFar()
{
    return m_far;
}