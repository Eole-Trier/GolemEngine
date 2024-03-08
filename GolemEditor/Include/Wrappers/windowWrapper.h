#pragma once

#define WINDOW_INTERFACE WindowWrapper::GetInstance()

struct GLFWwindow;
struct GLFWmonitor;

class WindowWrapper
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

	// Initialize window library
	int Init();
	// Set options of window
	void SetOption(int _hint, int _value);
	// Create window
	GLFWwindow* NewWindow(int _width, int _height, const char* _title, GLFWmonitor* _monitor, GLFWwindow* _share);
	// Terminate windowing library
	void Terminate();
	// Makes the window passed in parameter the window that will be set as active (to perform operations on...etc).
	void SetCurrentWindow(GLFWwindow* _window);
	// Process different events to the window
	void ProcessEvents();
	// Swap between front and back buffer to render (back) or display (front)
	void SwapBuffers(GLFWwindow* _window);
	// Check if user tried to close window
	int ShouldWindowClose(GLFWwindow* _window);
};