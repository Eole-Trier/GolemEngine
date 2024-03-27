#pragma once

#include "UI/Windows/window.h"


class BasicActors : public Window
{
public:
	BasicActors(std::string _name);
	~BasicActors();

	void Update() override;
};