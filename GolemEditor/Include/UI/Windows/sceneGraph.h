#pragma once

#include "UI/Windows/window.h"

class GolemEngine;

class SceneGraph : public Window
{
public:
	SceneGraph(std::string _name);
	~SceneGraph();

	void Update(GolemEngine* _golemEngine) override;
};