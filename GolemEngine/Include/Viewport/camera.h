#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <MathsLib/Vector3.h>
#include <MathsLib/matrix4.h>

#include "dll.h"



enum GOLEM_ENGINE_API CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class GOLEM_ENGINE_API Camera
{
public:
    static Camera* Instance;

    Vector3 Position;
    Vector3 Front;
    Vector3 Up;
    Vector3 Right;
    Vector3 WorldUp;
    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    float Near = 0.1f;
    float Far = 1000.f;

    

    Camera(Vector3 position = Vector3(0.0f, 0.0f, 3.0f), Vector3 up = Vector3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    Matrix4 GetViewMatrix();

    void ProcessKeyboard(CameraMovement direction, float _deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    void ProcessMouseScroll(float yoffset);
    void ProcessInput(GLFWwindow* window, float deltaTime);

private:
    void UpdateCameraVectors();
};