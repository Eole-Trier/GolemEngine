#include "UI/Windows/debugWindow.h"

#include "Wrappers/interfaceWrapper.h"
#include "golemEngine.h"

DebugWindow::DebugWindow() {}

DebugWindow::~DebugWindow() {}

void DebugWindow::Update(GolemEngine* _golemEngine, const char* _name)
{
	GOLEM_UI->Begin("Debug");
	GOLEM_UI->Text("deltaTime: %f", _golemEngine->GetDeltaTime());
	GOLEM_UI->Text("time: %f", _golemEngine->GetTime());
	GOLEM_UI->End();
}