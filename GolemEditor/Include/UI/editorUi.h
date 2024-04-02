#pragma once

#include <vector>
#include <string>

#include "vector2.h"
#include "Core/gameobject.h"


class Window;
struct GLFWwindow;

class EditorUi
{
private:
	static inline std::vector<Window*> m_windows;

public:
	static inline GameObject* selected = nullptr;

public:

	static void Init();
	static void BeginDockSpace();
	static void EndDockSpace();
	static void UpdateWindows();

	static Window* GetWindowByName(std::string _name);
	static Vector2 GetDockedWindowPosition(std::string _dockedWindowName);
};