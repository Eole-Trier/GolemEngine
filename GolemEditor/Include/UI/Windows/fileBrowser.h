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
	// Content Browser loop
	void ContentBrowser();
	
	void LastPath(std::filesystem::path& _currentPath);
	// Get ever file name
	const char* GetFileName(const char* _path);

	std::string GetFileExtension(const std::string& _fileName);

	void RightMouseClickEvent();

	void CreateFolder();
	
	void DeleteFolder(const std::string& _folderPath);

	std::string SelectedFolder;

private:

	const std::string m_editorDirectory = std::filesystem::current_path().string().c_str();

	std::filesystem::path m_currentDirectory;
};