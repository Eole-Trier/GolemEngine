#pragma once

struct GLFWwindow;
class EngineWindow;

class DebugWindow
{
public:
	GLFWwindow* window;

public:
	DebugWindow();
	~DebugWindow();

	void Render(EngineWindow* _engineWindow);
};