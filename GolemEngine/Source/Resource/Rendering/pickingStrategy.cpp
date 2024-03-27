#include "..\..\..\Include\Resource\Rendering\pickingStrategy.h"

unsigned int PickingStrategy::m_rbo;
unsigned int PickingStrategy::m_fbo;

PickingStrategy::PickingStrategy()
{
}

PickingStrategy::~PickingStrategy()
{
}

bool PickingStrategy::Init()
{
    return true;
}

void PickingStrategy::SetWVP(const Matrix4 _wvp)
{
    //glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, (const GLfloat*)_wvp.m);
}

void PickingStrategy::SetObjectIndex(int _objectIndex)
{
    glUniform1ui(m_objectIndexLocation, _objectIndex);
}

void PickingStrategy::DrawStartCB(int _drawIndex)
{
    glUniform1ui(m_drawIndexLocation, _drawIndex);
}
