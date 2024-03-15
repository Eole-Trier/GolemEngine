#include "inputManager.h"

#include <iostream>


void InputManager::Init(GLFWwindow* _window)
{
    std::cout << GLFW_MOUSE_BUTTON_LAST;
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
    std::cout << "mouse pos: " << _xPos << " " << _yPos << std::endl;
}

void InputManager::MouseButtonCallback(GLFWwindow* _window, int _button, int _action, int _mods)
{
    if (_action == GLFW_PRESS) {
        std::cout << "Mouse button " << _button << " pressed" << std::endl;
    }
    else if (_action == GLFW_RELEASE) {
        std::cout << "Mouse button " << _button << " released" << std::endl;
    }
}

void InputManager::MouseScrollCallback(GLFWwindow* _window, double _xOffset, double _yOffset)
{
}

void InputManager::SetWindow(GLFWwindow* _window)
{
    m_window = _window;
}