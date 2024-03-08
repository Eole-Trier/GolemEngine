#pragma once

#include "UI/editorWindow.h"

class FileBrowser : public EditorWindow
{
public:
	FileBrowser();
	~FileBrowser();

	void Update(GolemEngine* _golemEngine, const char* _name = "default window") override;
};