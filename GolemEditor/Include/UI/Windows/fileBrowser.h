#pragma once

#include <filesystem>
#include <string>

class GolemEngine;

class FileBrowser
{
public:
	bool renameDialogOpen = false;

public:
	FileBrowser();
	~FileBrowser();

	void Update(GolemEngine* _golemEngine, const char* _name = "default_window");

	void TreeNodes(std::filesystem::path _path);
	// Content Browser loop
	void ContentBrowser();
	
	void LastPath(std::filesystem::path& _currentPath);
	// Get ever file name
	const char* GetFileName(const char* _path);

	void ShowRenameFileDialog(bool* _p_open, std::filesystem::path& _filePath, std::string& _newFileName);

private:
	const std::string m_editorDirectory = std::filesystem::current_path().string().c_str();

	std::filesystem::path m_currentDirectory;

	std::string m_fileToRename;
	std::string m_test;
};