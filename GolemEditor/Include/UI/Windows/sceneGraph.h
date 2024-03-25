#pragma once

#include "UI/Windows/window.h"

class GolemEngine;
class GameObject;

class SceneGraph : public Window
{
public:
	
	SceneGraph(std::string _name);
	~SceneGraph();

	void Update(GolemEngine* _golemEngine) override;
	void DisplayObjects(GolemEngine* _golemEngine, GameObject* _gameObject);

private:
	GameObject* m_selected = nullptr;
	GameObject* m_renaming = nullptr;
};