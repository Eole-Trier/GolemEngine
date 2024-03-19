#include "..\..\Include\Inputs\Mouse.h"

Mouse::Mouse()
{
}

Mouse::~Mouse()
{
}

void Mouse::SelectObject(float _mouseX, float _mouseY)
{
    for (const auto& obj : objects)
    {
        if (ImGui::GetWindowSize().x >= obj.minX && ImGui::GetWindowSize().x <= obj.maxX && ImGui::GetWindowSize().y >= obj.minY && ImGui::GetWindowSize().y <= obj.maxY)
        {
            std::cout << "Object selected: " << obj.id << std::endl;
        }
    }
    std::cout << "No object selected." << std::endl;
}
