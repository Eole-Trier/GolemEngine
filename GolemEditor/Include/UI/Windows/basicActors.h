#pragma once

class GolemEngine;

class BasicActors 
{
public:
	BasicActors();
	~BasicActors();

	void Update(GolemEngine* _golemEngine, const char* _name = "default_window");
};