#pragma once

#include <string>

#include "dll.h"
#include "fragmentShader.h"
#include "Resource/resource.h"
#include "vertexShader.h"
#include "fragmentShader.h"


class GOLEM_ENGINE_API Shader : public Resource
{
private:
    VertexShader* m_vertexShader = nullptr;
    FragmentShader* m_fragmentShader = nullptr;
    
public:
    unsigned int id = 0;
    
public:
    Shader();

    void SetAllShaders(VertexShader* _vertexShader, FragmentShader* _fragmentShader);

    void Use();

    VertexShader* GetVertexShader();
    FragmentShader* GetFragmentShader();
};