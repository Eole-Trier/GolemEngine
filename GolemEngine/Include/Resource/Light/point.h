#pragma once

#include "dll.h"
#include "Resource/Light/Light.h"

class Shader;


class GOLEM_ENGINE_API PointLight : public Light
{
public:
    int id;
    Vector3 position;
    float constant;
    float linear;
    float quadratic;

    PointLight(const Vector4& diffuse, const Vector4& ambient, const Vector4& specular, const Vector3& position, const float constant, const float linear, const float quadratic, int id);
    void SetPointLight(Shader* shader);
   
};