#include <MathsLib/utils.h>
#include "Viewport/camera.h"



Camera::Camera(Vector3 position, Vector3 up, float yaw, float pitch)
    : Front(Vector3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    UpdateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : Front(Vector3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    Position = Vector3(posX, posY, posZ);
    WorldUp = Vector3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    UpdateCameraVectors();
}


Matrix4 Camera::GetViewMatrix()
{
    return Matrix4::LookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(CameraMovement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        Position = Position + Front * velocity;
    if (direction == BACKWARD)
        Position = Position - Front * velocity;
    if (direction == LEFT)
        Position = Position - Right * velocity;
    if (direction == RIGHT)
        Position = Position + Right * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}

void Camera::UpdateCameraVectors()
{
    Vector3 front;
    front.x = cos(DegToRad(Yaw)) * cos(DegToRad(Pitch));
    front.y = sin(DegToRad(Pitch));
    front.z = sin(DegToRad(Yaw)) * cos(DegToRad(Pitch));
    Front = front.Normalize();
    Right = Vector3::Cross(Front, WorldUp).Normalize();
    Up = Vector3::Cross(Right, Front).Normalize();
}