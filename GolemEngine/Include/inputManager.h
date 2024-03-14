#pragma once

#include "Wrappers/windowWrapper.h"

class InputManager
{
private:
	static inline GLFWwindow* m_window = nullptr;
	static inline bool m_keyboardKeys[LAST_KEY_INT];

private:
	// Static class
	InputManager() = delete;

public:
	static void Init(GLFWwindow* _window);
	static void KeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);
	static bool IsKeyPressed(int _key);

	static void SetWindow(GLFWwindow* _window);
};