#pragma once

#include "Viewport/scene.h"


class Viewport
{
public:
	Viewport();
	~Viewport();

	void Update(Scene* _scene);
};