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
    if (!Technique::Init()) 
    {
        return false;
    }

    if (!AddShader(GL_VERTEX_SHADER, "picking.vs")) 
    {
        return false;
    }

    if (!AddShader(GL_FRAGMENT_SHADER, "picking.fs")) 
    {
        return false;
    }

    if (!Finalize())
    {
        return false;
    }

    m_WVPLocation = GetUniformLocation("gWVP");
    m_objectIndexLocation = GetUniformLocation("gObjectIndex");
    m_drawIndexLocation = GetUniformLocation("gDrawIndex");

    if (m_WVPLocation == INVALID_UNIFORM_LOCATION || m_objectIndexLocation == INVALID_UNIFORM_LOCATION || m_drawIndexLocation == INVALID_UNIFORM_LOCATION)
    {
        return false;
    }

    return true;
}

void PickingStrategy::SetWVP(const Matrix4 _wvp)
{
    glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, (const GLfloat*)_wvp.m);
}

void PickingStrategy::SetObjectIndex(int _objectIndex)
{
    glUniform1ui(m_objectIndexLocation, _objectIndex);
}

void PickingStrategy::DrawStartCB(int _drawIndex)
{
    glUniform1ui(m_drawIndexLocation, _drawIndex);
}
