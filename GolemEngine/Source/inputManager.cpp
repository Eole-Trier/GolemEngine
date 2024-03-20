#include "inputManager.h"

#include <iostream>

#include "imgui.h"
#include "Viewport/camera.h"


Camera* InputManager::m_camera = nullptr;

float InputManager::m_mouseOffsetX = 0.0f;
float InputManager::m_mouseOffsetY = 0.0f;
bool InputManager::m_isFirstMouse = true;
float InputManager::m_lastX = 0.0f;
float InputManager::m_lastY = 0.0f;
float InputManager::m_scrollOffsetY = 0.0f;

void InputManager::Init(GLFWwindow* _window)
{
    glfwSetKeyCallback(_window, KeyCallback);
    glfwSetScrollCallback(_window, MouseScrollCallback);
}

void InputManager::KeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)
{
    if (_action == KEY_PRESSED)
    {
        m_keyboardKeys[_key] = true;
    }
    else if (_action == KEY_RELEASED)
    {
        if (m_keyboardKeys[_key] == true)
        {
            m_keyboardKeys[_key] = false;
        }
    }
}

bool InputManager::IsKeyPressed(int _key)
{
    return m_keyboardKeys[_key];
}

void InputManager::MousePositionCallback(GLFWwindow* _window, double _xPos, double _yPos)
{
    float xPos = (float)_xPos;
    float yPos = (float)_yPos;

    if (m_isFirstMouse) {
        m_lastX = xPos;
        m_lastY = yPos;
        m_isFirstMouse = false;
    }

    float xOffset = xPos - m_lastX;
    float yOffset = m_lastY - yPos;
    m_lastX = xPos;
    m_lastY = yPos;

    m_mouseOffsetX = xOffset;
    m_mouseOffsetY = -yOffset;  // Invert y coordinate
    //std::cout << m_mouseOffsetX << " , " << m_mouseOffsetY << std::endl;
}

void InputManager::MouseButtonCallback(GLFWwindow* _window, int _button, int _action, int _mods)
{
    if (_action == GLFW_PRESS)
    {
        std::cout << "Mouse button " << _button << " pressed" << std::endl;
    }
    else if (_action == GLFW_RELEASE) 
    {
        std::cout << "Mouse button " << _button << " released" << std::endl;
    }
}

void InputManager::MouseScrollCallback(GLFWwindow* _window, double _xOffset, double _yOffset)
{
    m_scrollOffsetY = -_yOffset;
}

float InputManager::GetMouseOffsetX()
{
    return m_mouseOffsetX;
}

float InputManager::GetMouseOffsetY()
{
    return m_mouseOffsetY;
}

float InputManager::GetScrollOffsetY()
{
    return m_scrollOffsetY;
}

void InputManager::SetWindow(GLFWwindow* _window)
{
    m_window = _window;
}

void InputManager::SetCamera(Camera* _camera)
{
    m_camera = _camera;
}

void InputManager::SetMouseOffsetX(float _value)
{
    m_mouseOffsetX = _value;
}

void InputManager::SetMouseOffsetY(float _value)
{
    m_mouseOffsetY = _value;
}