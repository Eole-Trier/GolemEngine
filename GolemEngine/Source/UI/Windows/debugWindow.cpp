#include "UI/Windows/debugWindow.h"

#include "Wrappers/interfaceWrapper.h"
#include "golemEngine.h"

DebugWindow::DebugWindow() {}

DebugWindow::~DebugWindow() {}

void DebugWindow::Update(GolemEngine* _golemEngine)
{
	InterfaceWrapper::GetInstance()->Begin("Debug");
	InterfaceWrapper::GetInstance()->Text("deltaTime: %f", _golemEngine->GetDeltaTime());
	InterfaceWrapper::GetInstance()->Text("time: %f", _golemEngine->GetTime());
	InterfaceWrapper::GetInstance()->End();
}