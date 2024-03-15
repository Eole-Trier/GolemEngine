#pragma once

#include "dll.h"
#include <GLFW/glfw3.h>

#define WINDOW_INTERFACE WindowWrapper::GetInstance()

struct GLFWwindow;
struct GLFWmonitor;

using Golemint = GLuint;
//using ScrollCallback = void(*)(double xoffset, double yoffset);

class GOLEM_ENGINE_API WindowWrapper
{
private:
	// Static pointer which points to the only instance of this class
	static WindowWrapper* m_instancePtr;

private:
	// Private constructor to stop intanciation
	WindowWrapper();

public:
	// Returns instance of the class
	static WindowWrapper* GetInstance();

	// Init GLFW
	void Init();
	// Create new GLFW window 
	GLFWwindow* NewWindow(int _width, int _height, const char* _title, GLFWmonitor* _monitor, GLFWwindow* _share);
	// Terminate in case of error
	void Terminate();
	// Check if user tried to close window
	int ShouldWindowClose(GLFWwindow* _window);
	// Process different events to the window
	void ProcessEvents();
	// Swap between front and back buffer to render (back) or display (front)
	void SwapBuffers(GLFWwindow* _window);

	// Gets active window
	GLFWwindow* GetCurrentWindow();
	// Makes the window passed in parameter the window that will be set as active (to perform operations on...etc).
	void SetCurrentWindow(GLFWwindow* _window);

	//void SetScrollCallback(ScrollCallback callback);

	GLuint LoadUITexture(const char* _filename);

private:
	//ScrollCallback m_scrollCallback;
};