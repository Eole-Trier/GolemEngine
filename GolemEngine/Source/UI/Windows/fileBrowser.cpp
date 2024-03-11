#include "UI/Windows/fileBrowser.h"

#include "imgui.h"
#include "ImGuiFileDialog-master/ImGuiFileDialog.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

FileBrowser::FileBrowser() {}

FileBrowser::~FileBrowser() {}

void FileBrowser::Update()
{
	ImGui::Begin("File_Browser");

    if (ImGui::Button("Open File Dialog"))
    {
        ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".cpp,.h,.hpp,.py", ".");
    }

    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
            std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
            system(filePathName.c_str());
        }

        ImGuiFileDialog::Instance()->Close();
    }

	ImGui::End();
}