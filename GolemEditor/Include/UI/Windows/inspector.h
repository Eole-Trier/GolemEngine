#pragma once

#include "UI/Windows/window.h"
#include "Core/gameobject.h"
#include "Core/transform.h"
#include "Refl/refl.hpp"
#include <iostream>
#include "imgui.h"
#include "imgui_stdlib.h"
#include "vector2.h"


class Inspector : public Window
{
private:
	const char* m_addComponentPopupId;
	const char* m_addComponentButtonName;
	Vector2 m_addComponentButtonSize;

public:
	Inspector(std::string _name);
	~Inspector();

	void Update() override;
	void AddComponentHandler();
};
	