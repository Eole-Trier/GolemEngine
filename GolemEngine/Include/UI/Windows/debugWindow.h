#pragma once

struct GLFWwindow;
class GolemEngine;

class DebugWindow
{
public:
	GLFWwindow* window;

public:
	DebugWindow();
	~DebugWindow();

	void Update(GolemEngine* _golemEngine);
};