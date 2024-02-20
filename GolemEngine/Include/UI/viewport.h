#pragma once

class Viewport
{
public:
	Viewport();
	~Viewport();

	void Render();

	void BeginDockSpace() const;
};