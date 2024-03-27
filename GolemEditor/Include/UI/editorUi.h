#pragma once

#include <vector>
#include <string>

#include "vector2.h"

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

	void Init();
	void BeginDockSpace();
	void EndDockSpace();
	void UpdateWindows();

	Window* GetWindowByName(std::string _name);
	Vector2 GetDockedWindowPosition(std::string _dockedWindowName);
};