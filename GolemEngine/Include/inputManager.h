#pragma once

#include "dll.h"
#include "Wrappers/windowWrapper.h"
#include "Viewport/camera.h"

class Camera;

class GOLEM_ENGINE_API InputManager
{
private:
	static inline GLFWwindow* m_window = nullptr;
	static Camera* m_camera;
	static inline bool m_keyboardKeys[LAST_KEY_INT];

	static float m_mouseOffsetX;
	static float m_mouseOffsetY;
	static bool m_firstMouse;
	static float m_lastX;
	static float m_lastY;

private:
	// Static class
	InputManager() = delete;

public:
	static void Init(GLFWwindow* _window, Camera* _camera);
	static void KeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);
	static bool IsKeyPressed(int _key);
	static void MousePositionCallback(GLFWwindow* _window, double _xPos, double _yPos);
	static void MouseButtonCallback(GLFWwindow* _window, int _button, int _action, int _mods);
	static void MouseScrollCallback(GLFWwindow* _window, double _xOffset, double _yOffset);

	static float GetMouseOffsetX();
	static float GetMouseOffsetY();

	static void SetWindow(GLFWwindow* _window);
	static void SetCamera(Camera* _camera);
	static void SetMouseOffsetX(float _value);
	static void SetMouseOffsetY(float _value);
};