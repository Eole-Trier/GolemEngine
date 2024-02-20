#pragma once

struct GLFWwindow;

class FileBrowser
{
public:
	GLFWwindow* window;

public:
	FileBrowser();
	~FileBrowser();

	void Render();
};