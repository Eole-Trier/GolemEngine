#pragma once

#include <filesystem>
#include <string>

#include "UI/Windows/window.h"

class GolemEngine;

class FileBrowser : public Window
{
public:
	FileBrowser(std::string _name);
	~FileBrowser();

	void Update(GolemEngine* _golemEngine) override;

	void TreeNodes(std::filesystem::path _path);
	// Content Browser loop
	void ContentBrowser();
	
	void LastPath(std::filesystem::path& _currentPath);
	// Get ever file name
	const char* GetFileName(const char* _path);


private:

	const std::string m_editorDirectory = std::filesystem::current_path().string().c_str();

	std::filesystem::path m_currentDirectory;
};