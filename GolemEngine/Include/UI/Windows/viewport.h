#pragma once
#include "UI/engineUi.h"
#include "Viewport/scene.h"

class GolemEngine;

class Viewport : Window
{
public:
	Viewport();
	~Viewport();

	void Update(GolemEngine* _golemEngine);
};