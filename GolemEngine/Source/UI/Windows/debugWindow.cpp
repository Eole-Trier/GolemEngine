#include "UI/Windows/debugWindow.h"

#include "Wrappers/interfaceWrapper0.h"
#include "golemEngine.h"

DebugWindow::DebugWindow() {}

DebugWindow::~DebugWindow() {}

void DebugWindow::Update(GolemEngine* _golemEngine, const char* _name)
{
	UI_INTERFACE->Begin("Debug");
	UI_INTERFACE->Text("deltaTime: %f", _golemEngine->GetDeltaTime());
	UI_INTERFACE->Text("time: %f", _golemEngine->GetTime());
	UI_INTERFACE->End();
}