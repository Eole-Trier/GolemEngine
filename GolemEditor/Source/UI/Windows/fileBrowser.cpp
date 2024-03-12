#include "UI/Windows/fileBrowser.h"

#include <filesystem>

#include "ImGuiFileDialog-master/ImGuiFileDialog.h"
#include "golemEngine.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

namespace fs = std::filesystem;

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
	ContentBrowser();
	ImGui::EndChild();

	ImGui::End();
}


void FileBrowser::TreeNodes(std::filesystem::path _path)
{
	bool test = std::filesystem::is_directory(_path);
	if (test)
	{
		if (ImGui::TreeNodeEx(_path.filename().string().c_str(), ImGuiTreeNodeFlags_OpenOnArrow))
		{
			for (const auto& entry : std::filesystem::directory_iterator(_path))
			{
				TreeNodes(entry);
			}
			ImGui::TreePop();
		}
	}
	else
	{
		ImGui::TreeNodeEx(_path.filename().string().c_str(), ImGuiTreeNodeFlags_Leaf);
		ImGui::TreePop();
	}
}

void FileBrowser::ContentBrowser()
{
	for (auto& p : fs::directory_iterator(m_currentDirectory))
	{
		std::string path = p.path().string();
		if (p.is_directory())
		{
			ImGui::SameLine();
			if (ImGui::Button(GetFileName(path.c_str())))
			{
				m_currentDirectory = path;
			}
		}
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
