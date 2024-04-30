#pragma once
#include "window.h"

extern bool g_isPlayTesting;

class PlayScene : public Window
{
public:
	int width = 0, height = 0;

	PlayScene(std::string _name);
	~PlayScene();

	void Update() override;
};