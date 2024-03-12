#pragma once

#include <filesystem>
#include <string>

class GolemEngine;

class FileBrowser
{
public:
	FileBrowser();
	~FileBrowser();

	void Update(GolemEngine* _golemEngine, const char* _name = "default_window");

	void TreeNodes(std::filesystem::path _path);

	void ContentBrowser();

	const char* GetFileName(const char* _path);

private:

	const std::string m_editorDirectory = std::filesystem::current_path().string().c_str();

	std::filesystem::path m_currentDirectory;
};