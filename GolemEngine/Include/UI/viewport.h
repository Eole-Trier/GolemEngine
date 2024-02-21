#pragma once

#include "Viewport/scene.h"


class Viewport
{
public:
	Viewport();
	~Viewport();

	void Render(Scene* _scene);
};