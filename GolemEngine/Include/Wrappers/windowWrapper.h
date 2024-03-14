#pragma once

#include <GLFW/glfw3.h>

#include "dll.h"

#pragma region InputManager defines
#define LAST_KEY_INT GLFW_KEY_LAST
#define KEY_PRESSED GLFW_PRESS
#define KEY_RELEASED GLFW_RELEASE

#define KEY_ESCAPE GLFW_KEY_ESCAPE
#define KEY_A GLFW_KEY_A
#define KEY_B GLFW_KEY_B
#define KEY_C GLFW_KEY_C
#define KEY_D GLFW_KEY_D
#define KEY_E GLFW_KEY_E
#define KEY_F GLFW_KEY_F
#define KEY_G GLFW_KEY_G
#define KEY_H GLFW_KEY_H
#define KEY_I GLFW_KEY_I
#define KEY_J GLFW_KEY_J
#define KEY_K GLFW_KEY_K
#define KEY_L GLFW_KEY_L
#define KEY_M GLFW_KEY_M
#define KEY_N GLFW_KEY_N
#define KEY_O GLFW_KEY_O
#define KEY_P GLFW_KEY_P
#define KEY_Q GLFW_KEY_Q
#define KEY_R GLFW_KEY_R
#define KEY_S GLFW_KEY_S
#define KEY_T GLFW_KEY_T
#define KEY_U GLFW_KEY_U
#define KEY_V GLFW_KEY_V
#define KEY_W GLFW_KEY_W
#define KEY_X GLFW_KEY_X
#define KEY_Y GLFW_KEY_Y
#define KEY_Z GLFW_KEY_Z
#pragma endregion InputManager defines

struct GLFWwindow;
struct GLFWmonitor;

//using ScrollCallback = void(*)(double xoffset, double yoffset);

class GOLEM_ENGINE_API WindowWrapper
{
private:
	static GLFWwindow* m_window;

private:
	// Static class
	WindowWrapper() = delete;

public:
	// Init GLFW
	static void InitWindow();
	// Create new GLFW window
	static GLFWwindow* NewWindow(int _width, int _height, const char* _title, GLFWmonitor* _monitor, GLFWwindow* _share);
	// Terminate in case of error
	static void Terminate();
	// Check if user tried to close window
	static int ShouldWindowClose(GLFWwindow* _window);
	// Process different events to the window
	static void ProcessEvents();
	// Swap between front and back buffer to render (back) or display (front)
	static void SwapBuffers(GLFWwindow* _window);

	// Gets active window
	static GLFWwindow* GetWindow();

	// Makes the window passed in parameter the window that will be set as active (to perform operations on...etc).
	static void SetCurrentWindow(GLFWwindow* _window);
	//void SetScrollCallback(ScrollCallback callback);

private:
	//ScrollCallback m_scrollCallback;
};