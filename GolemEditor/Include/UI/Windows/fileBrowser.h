#pragma once

class GolemEngine;

class FileBrowser
{
public:
	FileBrowser();
	~FileBrowser();

	void Update(GolemEngine* _golemEngine, const char* _name = "default_window");
};