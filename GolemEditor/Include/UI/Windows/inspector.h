#pragma once

#include "UI/Windows/window.h"

class GolemEngine;

class Inspector : public Window
{
public:
	Inspector(std::string _name);
	~Inspector();

	void Update(GolemEngine* _golemEngine) override;
};