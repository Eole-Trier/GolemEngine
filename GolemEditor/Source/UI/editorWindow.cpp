#include "UI/editorWindow.h"
#include "golemEngine.h"
#include "Wrappers/interfaceWrapper.h"

void EditorWindow::Update(GolemEngine* _golemEngine, const char* _name) {}

void TestWindow::Update(GolemEngine* _golemEngine, const char* _name)
{
	UI_INTERFACE->Begin("TestWindow");
	UI_INTERFACE->Text("Test");
	UI_INTERFACE->End();
}
