#include "UI/Windows/fileBrowser.h"

#include <filesystem>
#include <stack>

#include "ImGuiFileDialog-master/ImGuiFileDialog.h"
#include "golemEngine.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

namespace fs = std::filesystem;

#define EXCLUDE_FILE(name) \
    (name != "x64" && \
    name != "GolemEditor.vcxproj" && \
    name != "GolemEditor.vcxproj.filters" && \
    name != "GolemEditor.vcxproj.user" && \
    name != "imgui.ini")

FileBrowser::FileBrowser() 
	:m_currentDirectory(m_editorDirectory)
{}

FileBrowser::~FileBrowser() {}

void FileBrowser::Update(GolemEngine* _golemEngine, const char* _name)
{
	ImGui::Begin("File_Browser");

	ImGui::BeginChild("child1", ImVec2(ImGui::GetContentRegionAvail().x * 0.5f, 0), ImGuiChildFlags_Border | ImGuiChildFlags_ResizeX);
	TreeNodes(std::filesystem::current_path());
	ImGui::EndChild();

	ImGui::SameLine();
	ImGui::BeginChild("child2", ImVec2(0, 0), ImGuiChildFlags_Border);
	ImGui::Text(GetFileName(m_currentDirectory.string().c_str()));
	ImGui::Text("");
	ContentBrowser();
	ImGui::EndChild();

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
	if (m_currentDirectory != m_editorDirectory)
	{
		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 0.0f, 0.0f)); 
		ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.5f, 0.5f));
		ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(100.0f, 30.0f));
		if (ImGui::Button("<-Back"))
		{
			LastPath(m_currentDirectory);
		}
		ImGui::PopStyleColor();
		ImGui::PopStyleVar(2);
		ImGui::Text("");
	}

	for (auto& p : fs::directory_iterator(m_currentDirectory))
	{
		std::string path = p.path().string();
		std::string fileName = GetFileName(path.c_str());
		if (EXCLUDE_FILE(fileName))
		{
			ImGui::SameLine();
			if (ImGui::Button(GetFileName(path.c_str())))
			{
				if (p.is_directory())
				{
					m_currentDirectory = path;
				}
			}
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
