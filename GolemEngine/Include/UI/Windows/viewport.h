#pragma once

#include "Viewport/scene.h"

class GolemEngine;

class Viewport
{
public:
	Viewport();
	~Viewport();

	void Update(GolemEngine* golemEngine);
};