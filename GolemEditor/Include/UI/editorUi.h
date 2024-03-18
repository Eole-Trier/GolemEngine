#pragma once

#include <vector>
#include <string>

class GolemEngine;
class Window;
struct GLFWwindow;

class EditorUi
{
private:
	std::vector<Window*> m_windows;
	GolemEngine* m_golemEngine = nullptr;

public:
	EditorUi(GolemEngine* _golemEngine);

	void Init(GLFWwindow* _window);
	void BeginDockSpace();
	void EndDockSpace();
	void UpdateWindows();

	Window* GetWindowByName(std::string _name);
};