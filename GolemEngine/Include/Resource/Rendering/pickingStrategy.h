#pragma once
#include <iostream>

#include "Wrappers/graphicWrapper.h"
#include "texture.h"
#include "matrix4.h"
#include "renderCallbacks.h"
#include "technique.h"

#ifndef PICKING_TECHNIQUE_H
#define PICKING_TECHNIQUE_H

class PickingStrategy : public Technique, public IRenderCallbacks
{
private:
	static unsigned int m_fbo;
	static unsigned int m_rbo;

	GLuint m_WVPLocation;
	GLuint m_drawIndexLocation;
	GLuint m_objectIndexLocation;

public:
	PickingStrategy();
	~PickingStrategy();

	virtual bool Init();

	void SetWVP(const Matrix4 _wvp);

	void SetObjectIndex(int _objectIndex);

	void DrawStartCB(int _drawIndex);
};

#endif