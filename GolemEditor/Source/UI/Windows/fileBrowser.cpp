#include "UI/Windows/fileBrowser.h"

#include <filesystem>
#include <iostream>
#include <stack>

#include "golemEngine.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "ImGuiFileDialog-master/ImGuiFileDialog.h"
#include "Wrappers/windowWrapper.h"
#include "Resource/tools.h"

namespace fs = std::filesystem;

#define EXCLUDE_FILE(name) \
    (name != "x64" && \
    name != "GolemEditor.vcxproj" && \
    name != "GolemEditor.vcxproj.filters" && \
    name != "GolemEditor.vcxproj.user" && \
    name != "imgui.ini")

FileBrowser::FileBrowser(std::string _name)
	: Window(_name), m_currentDirectory(m_editorDirectory)
{
}

FileBrowser::~FileBrowser() {}

void FileBrowser::Update(GolemEngine* _golemEngine)
{
	ImGui::Begin("File_Browser");
	// Tree node
	ImGui::BeginChild("child1", ImVec2(ImGui::GetContentRegionAvail().x * 0.5f, 0), ImGuiChildFlags_Border | ImGuiChildFlags_ResizeX);
	TreeNodes(std::filesystem::current_path());
	ImGui::EndChild();
	ImGui::SameLine();

	// Content browser viewer
	ImGui::BeginChild("child2", ImVec2(0, 0), ImGuiChildFlags_Border);
	ContentBrowser();
	ImGui::EndChild();
	RightMouseClickEvent();
	ImGui::End();
}


void FileBrowser::TreeNodes(std::filesystem::path _path)
{
	std::stack<std::filesystem::path> stack;
	stack.push(_path);

	while (!stack.empty())
	{
		std::filesystem::path currentPath = stack.top();
		stack.pop();

		bool isDirectory = std::filesystem::is_directory(currentPath);

		ImGuiTreeNodeFlags flags = isDirectory ? ImGuiTreeNodeFlags_OpenOnArrow : ImGuiTreeNodeFlags_Leaf;

		if (ImGui::TreeNodeEx(currentPath.filename().string().c_str(), flags))
		{
			if (isDirectory)
			{
				ImGui::Indent();
				
				for (const auto& entry : std::filesystem::directory_iterator(currentPath))
				{
					stack.push(entry);
				}
			}
			ImGui::TreePop();
		}
	}
}

void FileBrowser::ContentBrowser()
{
	ImGui::Text(GetFileName(m_currentDirectory.string().c_str()));
	ImGui::Text("");
	if (m_currentDirectory != m_editorDirectory)
	{
		ImGui::SameLine();
		ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.5f, 0.5f));
		ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(100.0f, 30.0f));
		if (ImGui::Button("<-Back"))
		{
			LastPath(m_currentDirectory);
		}
		ImGui::PopStyleVar(2);
		ImGui::Text("");
	}

	for (auto& p : fs::directory_iterator(m_currentDirectory))
	{
		std::string path = p.path().string();
		std::string fileName = GetFileName(path.c_str());
		std::string extensionFile = GetFileExtension(fileName);
		if (EXCLUDE_FILE(fileName))
		{
			ImGui::BeginChild(GetFileName(path.c_str()), ImVec2(100, 100));
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
			if (ImGui::Button(GetFileName(path.c_str()), ImVec2(70, 70)))
			{
				if (p.is_directory())
				{
					m_currentDirectory = path;
				}
			}
			ImGui::PopStyleColor();
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 70);
			if (ImGui::IsMouseReleased(ImGuiMouseButton_Right) && ImGui::IsItemHovered())
			{
				std::cout << "right clicked this window" << path.c_str() << std::endl;
				// TODO a small menu
				ImGui::OpenPopup("FolderContextMenu");
				SelectedFolder = path;
			}

			if (p.is_directory())
			{
				Golemint texture = WindowWrapper::LoadUiTexture(Tools::FindFile("File_Icon.png").c_str());
				ImGui::Image((void*)(intptr_t)texture, ImVec2(70, 70));
			}
			else if (extensionFile == ".jpg" || extensionFile == ".png")
			{
				Golemint texture = WindowWrapper::LoadUiTexture(path.c_str());
				ImGui::Image((void*)(intptr_t)texture, ImVec2(70, 70));
			}
			else
			{
				Golemint texture = WindowWrapper::LoadUiTexture(Tools::FindFile("File_Icon.png").c_str());
				ImGui::Image((void*)(intptr_t)texture, ImVec2(70, 70));
			}
			ImGui::Text(GetFileName(path.c_str()));
			if (ImGui::BeginPopupContextItem("FolderContextMenu"))
			{
				if (ImGui::MenuItem("Delete"))
				{
					DeleteFolder(SelectedFolder.c_str());
				}
				ImGui::EndPopup();
			}
			ImGui::EndChild();
			ImGui::SameLine();
		}
	}
}

void FileBrowser::LastPath(std::filesystem::path& _currentPath)
{
	if (!_currentPath.empty())
	{
		fs::path parentPath = _currentPath.parent_path();
		_currentPath = parentPath;
	}
	else if (_currentPath == m_editorDirectory)
	{
		_currentPath = m_editorDirectory;
	}
}

const char* FileBrowser::GetFileName(const char* _path)
{
	if (_path == nullptr)
		return nullptr;

	int length = static_cast<int>(strlen(_path));
	int index = length - 1;

	while (index >= 0 && _path[index] != '\\')
	{
		--index;
	}

	return _path + index + 1;
}


std::string FileBrowser::GetFileExtension(const std::string& _fileName) 
{
	size_t dotPosition = _fileName.find_last_of('.');
	if (dotPosition != std::string::npos) {
		return _fileName.substr(dotPosition);
	}
	return "";
}

void FileBrowser::RightMouseClickEvent()
{
	if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(1))
	{
		ImGui::OpenPopup("Context Menu");
	}

	if (ImGui::BeginPopup("Context Menu"))
	{
		if (ImGui::MenuItem("New Folder"))
		{
			CreateFolder();
		}
		ImGui::EndPopup();
	}
}

void FileBrowser::CreateFolder()
{
	std::string newFolderName = "NewFolder";
	
	int count = 1;

	while (std::filesystem::exists(m_currentDirectory / newFolderName))
	{
		newFolderName = "NewFolder" + std::to_string(count);
		count++;
	}
	try
	{
		std::filesystem::create_directories(m_currentDirectory / newFolderName);
	}
	catch (const std::exception& e)
	{
		std::cerr << "Failed to create folder: " << e.what() << std::endl;
		return;
	}
}

void FileBrowser::DeleteFolder(const std::string& _folderPath)
{
	try
	{
		std::filesystem::remove_all(_folderPath);
		std::cout << "Folder " << _folderPath << "deleted successfully." << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Failed to delete folder: " << e.what() << std::endl;
	}
}
