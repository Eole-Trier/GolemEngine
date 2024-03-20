#pragma once
#include "golemEngine.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

#include "Core/gameobject.h"
#include "Viewport/scene.h"

#include <iostream>

class Mouse
{
public :
	std::vector<GameObject*> objects;

public:
	Mouse();
	~Mouse();

	void SelectObject(float _mouseX, float _mouseY);
};