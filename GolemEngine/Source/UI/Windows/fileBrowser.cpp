#include "UI/Windows/fileBrowser.h"

#include "ImGuiFileDialog-master/ImGuiFileDialog.h"
#include "Wrappers/interfaceWrapper.h"
#include "golemEngine.h"

FileBrowser::FileBrowser() {}

FileBrowser::~FileBrowser() {}

void FileBrowser::Update(GolemEngine* _golemEngine, const char* _name)
{
	InterfaceWrapper::GetInstance()->Begin("File_Browser");

    if (InterfaceWrapper::GetInstance()->Button("Open File Dialog"))
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

	InterfaceWrapper::GetInstance()->End();
}