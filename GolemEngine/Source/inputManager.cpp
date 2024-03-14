#include "inputManager.h"

#include <iostream>


void InputManager::Init(GLFWwindow* _window)
{
    glfwSetKeyCallback(_window, KeyCallback);
}

void InputManager::KeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)
{
    if (_action == KEY_PRESSED)
    {
        m_keyboardKeys[_key] = true;
        std::cout << _key << " is pressed" << std::endl;
    }
    else if (_action == KEY_RELEASED)
    {
        if (m_keyboardKeys[_key] == true)
        {
            m_keyboardKeys[_key] = false;
            std::cout << _key << " is released" << std::endl;
        }
    }
}

bool InputManager::IsKeyPressed(int _key)
{
    return m_keyboardKeys[_key];
}

void InputManager::SetWindow(GLFWwindow* _window)
{
    m_window = _window;
}