#pragma once
#include "UI/engineUi.h"

class FileBrowser : public Window
{
public:
	FileBrowser();
	~FileBrowser();

	void Update(GolemEngine* _golemEngine, const char* _name = "default window") override;
};