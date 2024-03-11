#include "UI/Windows/fileBrowser.h"

#include "imgui.h"
#include "ImGuiFileDialog-master/ImGuiFileDialog.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"*



FileBrowser::FileBrowser() {}

FileBrowser::~FileBrowser() {}

void FileBrowser::Update()
{
	Init();
	//ImGui::ShowDemoWindow();
}

void FileBrowser::Init()
{
	ImGui::Begin("File_Browser");

	ImGui::BeginChild("child1", ImVec2(ImGui::GetContentRegionAvail().x * 0.5f, 0), ImGuiChildFlags_Border | ImGuiChildFlags_ResizeX);
	TreeNodes(std::filesystem::current_path());
	ImGui::EndChild();

	ImGui::SameLine();
	ImGui::BeginChild("child2", ImVec2(0, 0), ImGuiChildFlags_Border);
	ImGui::EndChild();

	ImGui::End();
}

void FileBrowser::TreeNodes(std::filesystem::path path)
{
	bool test = std::filesystem::is_directory(path);

	if (test)
	{
		if (ImGui::TreeNodeEx(path.filename().string().c_str(), ImGuiTreeNodeFlags_OpenOnArrow))
		{
			for (const auto& entry : std::filesystem::directory_iterator(path))
			{
				TreeNodes(entry);
			}

			ImGui::TreePop();
		}
	}

	else
	{
		ImGui::TreeNodeEx(path.filename().string().c_str(), ImGuiTreeNodeFlags_Leaf);
		ImGui::TreePop();
	}
}

