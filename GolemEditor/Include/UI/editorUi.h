#pragma once

class GolemEngine;

class EditorUi
{
private:
	GolemEngine* m_golemEngine;

public:
	EditorUi(GolemEngine* _golemEngine);

	void Update();
};