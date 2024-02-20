#pragma once

#include <string>
#include "dll.h"

class Scene;
class Camera;
struct GLFWwindow;

class GOLEM_ENGINE_API Window
{
private:
	GLFWwindow* m_window = nullptr;
	std::string m_name;
	float m_lastFrame = 0;

	static float m_lastX;
	static float m_lastY;
	static float m_yaw;
	static float m_pitch;
	static bool m_firstMouse;

public:
	unsigned int width = 800;
	unsigned int height = 600;
	float DeltaTime;

public:
	Window();
	~Window();
	Window(const char* _name, unsigned int _width, unsigned int _height);

	GLFWwindow* GetWindow();

	void Init();
	void Render(Scene* _scene);
	void Close();



	void UpdateDeltaTime();

	void ImGuiInit();
	void ImGuiLoop();
	void ImGuiClean();

	void ProcessInput(Camera& _camera);

	static void ResizeCallback(GLFWwindow* window, int width, int height);
	static void MouseCallback(GLFWwindow* window, double xposIn, double yposIn);
	static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};