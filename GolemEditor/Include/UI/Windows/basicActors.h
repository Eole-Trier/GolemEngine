#pragma once

#include "UI/Windows/window.h"

class GolemEngine;

class BasicActors : public Window
{
public:
	BasicActors(std::string _name);
	~BasicActors();

	void Update(GolemEngine* _golemEngine) override;
};