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
#include "Viewport/scene.h"
#include "Core/gameobject.h"

namespace fs = std::filesystem;

// Avoid deleting important files that users do not have access to
#define EXCLUDE_FILE(name) \
    (name != "x64" && \
    name != "GolemEditor.vcxproj" && \
    name != "GolemEditor.vcxproj.filters" && \
    name != "GolemEditor.vcxproj.user" && \
    name != "imgui.ini")


FileBrowser::FileBrowser(std::string _name)
	: 
	Window(_name), 
	m_currentDirectory(m_editorDirectory)
{}

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
	
	// Drag and drop event
	DragandDropEvent();
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
	// Make it on sameline
	ImGui::Text(GetFolderName(m_currentDirectory.string().c_str()));
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

	if (!isLoadUi)
	{
		// Load every file's default UI
		Ui_Default = WindowWrapper::LoadUiTexture(Tools::FindFile("default_Ui.png").c_str());
		Ui_Folder = WindowWrapper::LoadUiTexture(Tools::FindFile("File_Icon.png").c_str());
		Ui_Cpp = WindowWrapper::LoadUiTexture(Tools::FindFile("cpp_Icon.png").c_str());;
		Ui_H = WindowWrapper::LoadUiTexture(Tools::FindFile("h_Icon.png").c_str());
		Ui_Obj = WindowWrapper::LoadUiTexture(Tools::FindFile("obj_Icon.png").c_str());
		// Do once
		isLoadUi = true;
	}

	// For displaying all files in this folder path
	for (auto& p : fs::directory_iterator(m_currentDirectory))
	{
		std::string path = p.path().string();
		std::string fileName = GetFolderName(path.c_str());
		// Get the extension like .obj .cpp .h ....
		std::string extensionFile = GetFileExtension(fileName);
		if (EXCLUDE_FILE(fileName))
		{
			// Every file is a small imgui window
			ImGui::BeginChild(GetFolderName(path.c_str()), ImVec2(100, 100));
			// Check the mouse is on the UI or not
			// if it is on the UI show the button 
			if (ImGui::IsMouseHoveringRect(ImGui::GetWindowPos(), ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowSize().x, ImGui::GetWindowPos().y + ImGui::GetWindowSize().y)))
			{
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
				// the UI is a button that we can click it to tigger new event
				if (ImGui::Button(GetFolderName(path.c_str()), ImVec2(70, 70)))
				{
					double currentTime = ImGui::GetTime();
					double clickInterval = currentTime - m_buttonState.lastClickTime;
					m_buttonState.lastClickTime = currentTime;
					if (p.is_directory() && clickInterval < ImGui::GetIO().MouseDoubleClickTime)
					{
						m_currentDirectory = path;
						m_buttonState.clicked = false;
					}
				}
				ImGui::PopStyleColor();
				ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 70);
			}
			// Right click to open content menu
			if (ImGui::IsMouseReleased(ImGuiMouseButton_Right) && ImGui::IsItemHovered())
			{
				ImGui::OpenPopup("FolderContextMenu");
				selectedFolder = path;
			}
			
			if (ImGui::BeginDragDropSource())
			{
				draggingFilePath = path;
				if (!p.is_directory())
					ImGui::SetDragDropPayload("FileDrop", draggingFilePath.c_str(), strlen(draggingFilePath.c_str()) + 1);
				isDragging = true;
				ImGui::EndDragDropSource();
			}

			// Show UI ICON
			if (p.is_directory())
			{
				ImGui::Image((void*)(intptr_t)Ui_Folder, ImVec2(70, 70));
			}
			// Show Texture image
			else if (extensionFile == ".jpg" || extensionFile == ".png")
			{
				auto it = std::find_if(m_loadedTextures.begin(), m_loadedTextures.end(), [&](const std::pair<std::string, GLuint>& element) {
					return element.first == path;
					});
				if (it != m_loadedTextures.end()) {
					ImGui::Image((void*)(intptr_t)it->second, ImVec2(70, 70));
				}
				else {
					GLuint texture = WindowWrapper::LoadUiTexture(path.c_str());
					ImGui::Image((void*)(intptr_t)texture, ImVec2(70, 70));
					m_loadedTextures.push_back(std::make_pair(path, texture)); 
				}
			}
			else if (extensionFile == ".cpp")
			{
				ImGui::Image((void*)(intptr_t)Ui_Cpp, ImVec2(70, 70));
			}
			else if (extensionFile == ".h")
			{
				ImGui::Image((void*)(intptr_t)Ui_H, ImVec2(70, 70));
			}
			else if (extensionFile == ".obj")
			{
				ImGui::Image((void*)(intptr_t)Ui_Obj, ImVec2(70, 70));
			}
			else
			{
				ImGui::Image((void*)(intptr_t)Ui_Default, ImVec2(70, 70));
			}
			// Show content menu
			// Menu selections:
			// Add to scene
			// Rename
			// Delete
			ImGui::Text(GetFolderName(path.c_str()));
			if (ImGui::BeginPopupContextItem("FolderContextMenu"))
			{
				if (ImGui::MenuItem("Add to scene"))
				{
					// TODO
				}
				if (ImGui::MenuItem("Rename"))
				{
					// TODO
				}
				if (ImGui::MenuItem("Delete"))
				{
					DeleteFolder(selectedFolder.c_str());
				}
				ImGui::EndPopup();
			}
			ImGui::EndChild();
			ImGui::SameLine();
		}
	}
}

// Record the previous file path for the back button
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
// Get the file name with after the last "\"
const char* FileBrowser::GetFolderName(const char* _path)
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

// Get the file extentension like .obj .cpp .h ......
std::string FileBrowser::GetFileExtension(const std::string& _fileName) 
{
	size_t dotPosition = _fileName.find_last_of('.');
	if (dotPosition != std::string::npos) {
		return _fileName.substr(dotPosition);
	}
	return "";
}

// Right click in file viewer
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

// Create a new folder 
void FileBrowser::CreateFolder()
{
	// with default name "NewFolder"
	std::string newFolderName = "NewFolder";
	
	int count = 1;

	// If it already exsits "NewFolder", add a number at the tail
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
		const char* folderName = GetFolderName(_folderPath.c_str());
		// Avoid deleting the important folders
		const std::vector<const char*> protectedFolders = { "Assets", "Source", "Include", "Shaders" };

		if (std::find(protectedFolders.begin(), protectedFolders.end(), folderName) == protectedFolders.end())
		{
			std::filesystem::remove_all(_folderPath);
			std::cout << "Folder " << _folderPath << " deleted successfully." << folderName << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Failed to delete folder: " << e.what() << std::endl;
	}

}

void FileBrowser::LoadFile(const std::string& _filePath)
{
	// TODO
}

void FileBrowser::DragandDropEvent()
{
	if (isDragging)
	{
		ImVec2 mousePos = ImGui::GetMousePos();
		ImVec2 windowPos = ImVec2(mousePos.x - 35, mousePos.y - 35);

		ImGui::SetNextWindowPos(windowPos);
		ImGui::Begin("Dragging Window", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
		// Show a drop Icon UI
		ImGui::Image((void*)(intptr_t)Ui_Default, ImVec2(70, 70));
		ImGui::End();
	}
	// If we released the mouse left button will trigger event
	if (ImGui::IsMouseReleased(0))
	{
		isDragging = false;
		std::cout << GetFolderName(draggingFilePath.c_str()) << std::endl;
	}
}
