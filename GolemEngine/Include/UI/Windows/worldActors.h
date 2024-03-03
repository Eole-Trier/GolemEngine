#pragma once

struct GLFWwindow;

class WorldActors
{
public:
	GLFWwindow* window;

public:
	WorldActors();
	~WorldActors();

	void Update();
};