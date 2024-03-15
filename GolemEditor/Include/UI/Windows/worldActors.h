#pragma once

class GolemEngine;

class WorldActors
{
public:
	WorldActors();
	~WorldActors();

	void Update(GolemEngine* _golemEngine, const char* _name = "default_window");
};