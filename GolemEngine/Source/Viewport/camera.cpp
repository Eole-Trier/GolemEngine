#include "Viewport/camera.h"

#include "utils.h"
#include "inputManager.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


Camera* Camera::instance;

Camera::Camera(Vector3 _position, Vector3 _up, float _yaw, float _pitch)
    : front(Vector3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
{
    zNear = 0.1f;
    zFar = 1000.f;
    minSpeed = 1.0f;
    maxSpeed = 100.0f;
    position = _position;
    worldUp = _up;
    yaw = _yaw;
    pitch = _pitch;
    UpdateCameraVectors();
    if (instance == nullptr)
        instance = this;
}

Camera::Camera(float _posX, float _posY, float _posZ, float _upX, float _upY, float _upZ, float _yaw, float _pitch)
    : front(Vector3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
{
    zNear = 0.1f;
    zFar = 1000.f;
    position = Vector3(_posX, _posY, _posZ);
    worldUp = Vector3(_upX, _upY, _upZ);
    yaw = yaw;
    pitch = pitch;
    UpdateCameraVectors();
    if (instance == nullptr)
        instance = this;
}


Matrix4 Camera::GetViewMatrix()
{
    return Matrix4::LookAt(position, position + front, up);
}

void Camera::ProcessKeyboard(CameraMovement _direction, float _deltaTime)
{
    float velocity = movementSpeed * _deltaTime;
    if (_direction == FORWARD)
        position = position + front * velocity;
    if (_direction == BACKWARD)
        position = position - front * velocity;
    if (_direction == LEFT)
        position = position - right * velocity;
    if (_direction == RIGHT)
        position = position + right * velocity;
    if (_direction == UP)
        position = position + up * velocity;
    if (_direction == DOWN)
        position = position - up * velocity;
}

void Camera::ProcessMouseMovement(float _xoffset, float _yoffset, GLboolean _constrainPitch)
{
    _xoffset *= mouseSensitivity;
    _yoffset *= mouseSensitivity;

    yaw += _xoffset;
    pitch += _yoffset;

    if (_constrainPitch)
    {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float _yoffset)
{
    if (movementSpeed + _yoffset > maxSpeed || movementSpeed + _yoffset < minSpeed)
        return;
    movementSpeed += (float)_yoffset;
}

void Camera::ProcessInput(GLFWwindow* _window, float _deltaTime)
{
    if (InputManager::IsKeyPressed(KEY_W))
    {
        ProcessKeyboard(CameraMovement::FORWARD, _deltaTime);
    }
    if (InputManager::IsKeyPressed(KEY_S))
    {
        ProcessKeyboard(CameraMovement::BACKWARD, _deltaTime);
    }
    if (InputManager::IsKeyPressed(KEY_A))
    {
        ProcessKeyboard(CameraMovement::LEFT, _deltaTime);
    }
    if (InputManager::IsKeyPressed(KEY_D))
    {
        ProcessKeyboard(CameraMovement::RIGHT, _deltaTime);
    }
    if (InputManager::IsKeyPressed(KEY_Q))
    {
        ProcessKeyboard(CameraMovement::UP, _deltaTime);
    }
    if (InputManager::IsKeyPressed(KEY_E))
    {
        ProcessKeyboard(CameraMovement::DOWN, _deltaTime);
    }
}

void Camera::UpdateCameraVectors()
{
    front.x = cos(DegToRad(yaw)) * cos(DegToRad(pitch));
    front.y = sin(DegToRad(pitch));
    front.z = sin(DegToRad(yaw)) * cos(DegToRad(pitch));
    front = front.Normalize();
    right = Vector3::Cross(front, worldUp).Normalize();
    up = Vector3::Cross(right, front).Normalize();
}
