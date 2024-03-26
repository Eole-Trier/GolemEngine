#pragma once
#include <iostream>

#include "Wrappers/graphicWrapper.h"

class PickingStrategy
{
private:
	static unsigned int m_fbo;
	static unsigned int m_rbo;

public:

	GLuint m_pickingTexture = 0;
	GLuint m_depthTexture = 0;

	struct PixelInfo
	{
		int objectID = 0;
		int drawID = 0;
		int primID = 0;

		void print()
		{
			printf("Objects %d draw %d prim &d\n", objectID, drawID, primID);
		}
	};

	PickingStrategy();
	~PickingStrategy();

	void InitPickingTexture(unsigned int _windowWidth, unsigned int _windowHeight);
	void InitMesh();
	PixelInfo ReadPixel(unsigned int x, unsigned int y);
	void EnableWriting();
	void DisableWriting();
	static void PickingPhase();
};