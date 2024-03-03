#include <MathsLib/utils.h>
#include "Viewport/camera.h"


Camera* Camera::Instance;

Camera::Camera(Vector3 position, Vector3 up, float yaw, float pitch)
    : Front(Vector3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    UpdateCameraVectors();
    if (Instance == nullptr)
        Instance = this;
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : Front(Vector3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    Position = Vector3(posX, posY, posZ);
    WorldUp = Vector3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    UpdateCameraVectors();
    if (Instance == nullptr)
        Instance = this;
}


Matrix4 Camera::GetViewMatrix()
{
    return Matrix4::LookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(CameraMovement direction, float _deltaTime)
{
    float velocity = MovementSpeed * _deltaTime;
    if (direction == FORWARD)
        Position = Position + Front * velocity;
    if (direction == BACKWARD)
        Position = Position - Front * velocity;
    if (direction == LEFT)
        Position = Position - Right * velocity;
    if (direction == RIGHT)
        Position = Position + Right * velocity;
    if (direction == UP)
        Position = Position + Up * velocity;
    if (direction == DOWN)
        Position = Position - Up * velocity;
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
    if (Zoom > 89.1f)
        Zoom = 89.1f;
}

void Camera::ProcessInput(GLFWwindow* window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        ProcessKeyboard(CameraMovement::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        ProcessKeyboard(CameraMovement::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        ProcessKeyboard(CameraMovement::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        ProcessKeyboard(CameraMovement::RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        ProcessKeyboard(CameraMovement::UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        ProcessKeyboard(CameraMovement::DOWN, deltaTime);
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
