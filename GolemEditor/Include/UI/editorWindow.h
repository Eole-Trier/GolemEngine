#pragma once

class GolemEngine;

class EditorWindow
{
public:
	virtual void Update(GolemEngine* _golemEngine, const char* _name = "default window");
private:
	const char* m_name;

};

class TestWindow : public EditorWindow
{
public:
	void Update(GolemEngine* _golemEngine, const char* _name = "default window") override;
};