#include "Resource/Rendering/Shader/computeShader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "Wrappers/graphicWrapper.h"


ComputeShader::ComputeShader(const char* _computePath)
    : m_computePath(_computePath)
{
    Init();
}

void ComputeShader::Init()
{
    
}
