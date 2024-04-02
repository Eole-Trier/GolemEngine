#pragma once

#include "UI/Windows/window.h"

class ToolBar : public Window
{
public:
	ToolBar(std::string _name);
	~ToolBar();

	void Update() override;
};