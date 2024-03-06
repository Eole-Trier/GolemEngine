#pragma once
#include "UI/engineUi.h"
struct GLFWwindow;

class BasicActors : Window
{
public:
	int a = 1;

public:
	BasicActors();
	~BasicActors();

	void Update();
};