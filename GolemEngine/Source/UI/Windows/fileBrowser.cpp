#include "UI/Windows/fileBrowser.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

FileBrowser::FileBrowser() {}

FileBrowser::~FileBrowser() {}

void FileBrowser::Update()
{
	ImGui::Begin("File_Browser");
	ImGui::End();
}