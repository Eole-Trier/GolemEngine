#pragma once
#include "UI/engineUi.h"
struct GLFWwindow;
class GolemEngine;

class DebugWindow : public Window
{
public:
	DebugWindow();
	~DebugWindow();

	void Update(GolemEngine* _golemEngine);
};