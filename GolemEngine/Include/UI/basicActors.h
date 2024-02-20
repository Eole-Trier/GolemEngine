#pragma once

struct GLFWwindow;

class BasicActors
{
public:
	GLFWwindow* window;

public:
	BasicActors();
	~BasicActors();

	void Render();
};