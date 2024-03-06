#include <MathsLib/utils.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Viewport/camera.h"
#include "UI/engineUi.h"

Camera* Camera::instance;

Camera::Camera(Vector3 _position, Vector3 _up, float _yaw, float _pitch)
    : front(Vector3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
{
    zNear = 0.1f;
    zFar = 1000.f;
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
    zoom -= (float)_yoffset;
    if (zoom < 1.0f)
        zoom = 1.0f;
    if (zoom > 89.1f)
        zoom = 89.1f;
}

void Camera::ProcessInput(GLFWwindow* _window, float _deltaTime)
{
    if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
        ProcessKeyboard(CameraMovement::FORWARD, _deltaTime);
    if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
        ProcessKeyboard(CameraMovement::BACKWARD, _deltaTime);
    if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
        ProcessKeyboard(CameraMovement::LEFT, _deltaTime);
    if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
        ProcessKeyboard(CameraMovement::RIGHT, _deltaTime);
    if (glfwGetKey(_window, GLFW_KEY_Q) == GLFW_PRESS)
        ProcessKeyboard(CameraMovement::UP, _deltaTime);
    if (glfwGetKey(_window, GLFW_KEY_E) == GLFW_PRESS)
        ProcessKeyboard(CameraMovement::DOWN, _deltaTime);
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
