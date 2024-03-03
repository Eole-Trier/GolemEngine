#pragma once

struct GLFWwindow;

class BasicActors
{
public:
	GLFWwindow* window;
	int a = 1;

public:
	BasicActors();
	~BasicActors();

	void Update();
};