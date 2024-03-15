#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <MathsLib/vector3.h>
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
    static Camera* instance;

    Vector3 position;
    Vector3 front;
    Vector3 up;
    Vector3 right;
    Vector3 worldUp;

    float yaw;
    float pitch;
    float movementSpeed;
    float minSpeed;
    float maxSpeed;
    float mouseSensitivity;
    float zoom;
    float zNear;
    float zFar;

    bool isMoved = false;
private:
    void UpdateCameraVectors();

public:
    Camera(Vector3 _position = Vector3(0.0f, 0.0f, 3.0f), Vector3 _up = Vector3(0.0f, 1.0f, 0.0f), float _yaw = YAW, float _pitch = PITCH);
    Camera(float _posX, float _posY, float _posZ, float _upX, float _upY, float _upZ, float _yaw, float _pitch);

    Matrix4 GetViewMatrix();
    void ProcessKeyboard(CameraMovement _direction, float _deltaTime);
    void ProcessMouseMovement(float _xoffset, float _yoffset, GLboolean _constrainPitch = true);
    void ProcessMouseScroll(float _yoffset);
    void ProcessInput(GLFWwindow* _window, float _deltaTime);
};