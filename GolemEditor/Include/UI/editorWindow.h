#pragma once
#include "golemEngine.h"

class EditorWindow
{
public:
	virtual void Update(GolemEngine* _golemEngine);

private:
	const char* m_name;

};