#pragma once

#include <string>

class GolemEngine;

class Window
{
public:
	std::string name;

public:
	Window(std::string _name);
	virtual void Update(GolemEngine* _golemEngine) = 0;
};