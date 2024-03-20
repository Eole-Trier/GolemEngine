#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "UI/Windows/window.h"
#include "Wrappers/windowWrapper.h"

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

	std::string GetFileExtension(const std::string& _fileName);

	void RightMouseClickEvent();

	void CreateFolder();
	
	void DeleteFolder(const std::string& _folderPath);

	// TODO RENAME

	void LoadFile(const std::string& _filePath);

	std::string selectedFolder;

	std::string draggingFilePath;

	bool isDragging = false;

	Golemint Ui_Folder;
	Golemint Ui_Cpp;
	Golemint Ui_H;
	Golemint Ui_Obj;

	struct ButtonState
	{
		bool clicked = false;
		double lastClickTime = -1.0;
	};

private:

	ButtonState m_buttonState;

	const std::string m_editorDirectory = std::filesystem::current_path().string().c_str();

	std::filesystem::path m_currentDirectory;
};