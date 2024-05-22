#pragma once

#include <vector3.h>

#include "dll.h"
#include "Core/camera.h"


class GOLEM_ENGINE_API Brush
{
private:
    Camera* m_camera = nullptr;
public:
    float radius;
    float force;

public:
    Brush(Camera* _camera);

    void Update();
    Vector3 CalculateMouseRay(int _width, int _height, int _mouseX, int _mouseY, Camera* _camera);
    Vector2 GetNormalisedDeviceCoordinates(int _width, int _height, float _mouseX, float _mouseY);
    Vector4 ToEyeCoords(Vector4 _clipCoords, Camera* _camera);
    
};
