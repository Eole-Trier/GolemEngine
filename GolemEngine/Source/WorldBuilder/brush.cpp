#include "WorldBuilder/brush.h"

Brush::Brush(Camera* _camera)
    : m_camera(_camera) {}

void Brush::Update()
{
}

Vector3 Brush::CalculateMouseRay(int _width, int _height, int _mouseX, int _mouseY, Camera* _camera)
{
    Vector2 mousePosNormalized = GetNormalisedDeviceCoordinates(_width, _height, _mouseX, _mouseY);
    Vector4 mouseClipSpace = Vector4(mousePosNormalized.x, mousePosNormalized.y, -1.0f, 1.0f);
    Vector4 mouseEyeSpace = ToEyeCoords
    
    return Vector3(0, 0, 0);
}

Vector2 Brush::GetNormalisedDeviceCoordinates(int _width, int _height, float _mouseX, float _mouseY)
{
    float x = (2.0f * (float)_mouseX) / (float)_width - 1.0f;
    float y = (2.0f * (float)_mouseY) / (float)_height - 1.0f;
    return Vector2(x, -y);
}

Vector4 Brush::ToEyeCoords(Vector4 _clipCoords, Camera* _camera)
{
    float aspectRatio = 
}
