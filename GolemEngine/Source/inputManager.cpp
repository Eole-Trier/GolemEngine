#include "inputManager.h"

#include <iostream>

#include "Viewport/camera.h"


Camera* InputManager::m_camera = nullptr;
float InputManager::m_mouseOffsetX = 0.0f;
float InputManager::m_mouseOffsetY = 0.0f;
bool InputManager::m_firstMouse = true;
float InputManager::m_lastX = 0.0f;
float InputManager::m_lastY = 0.0f;

void InputManager::Init(GLFWwindow* _window, Camera* _camera)
    //: m_camera(_camera) 
{
    std::cout << GLFW_MOUSE_BUTTON_LAST << std::endl;
    glfwSetKeyCallback(_window, KeyCallback);
    glfwSetCursorPosCallback(_window, MousePositionCallback);
    glfwSetMouseButtonCallback(_window, MouseButtonCallback);
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

    if (m_firstMouse) {
        m_lastX = xPos;
        m_lastY = yPos;
        m_firstMouse = false;
    }

    float xOffset = xPos - m_lastX;
    float yOffset = m_lastY - yPos;
    m_lastX = xPos;
    m_lastY = yPos;

    m_mouseOffsetX = xOffset;
    m_mouseOffsetY = -yOffset;  // Invert y coordinate

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
    
}

float InputManager::GetMouseOffsetX()
{
    return m_mouseOffsetX;
}

float InputManager::GetMouseOffsetY()
{
    return m_mouseOffsetY;
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