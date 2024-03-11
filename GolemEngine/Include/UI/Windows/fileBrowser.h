#pragma once
#include "UI/engineUi.h"

#include <filesystem>
#include <string>

class FileBrowser : Window
{
public:
	FileBrowser();
	~FileBrowser();

	void Init();

	void TreeNodes(std::filesystem::path path);

	void Update();
};