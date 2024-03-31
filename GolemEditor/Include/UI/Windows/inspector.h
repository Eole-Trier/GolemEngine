#pragma once

#include "UI/Windows/window.h"
#include "Core/gameobject.h"
#include "Core/transform.h"
#include "Refl/refl.hpp"
#include <iostream>
#include "imgui.h"
#include "imgui_stdlib.h"

class GolemEngine;

class Inspector : public Window
{
public:
	Inspector(std::string _name);
	~Inspector();

	void Update(GolemEngine* _golemEngine) override;
};
	