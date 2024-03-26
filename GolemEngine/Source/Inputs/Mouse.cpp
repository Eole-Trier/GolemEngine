#include "..\..\Include\Inputs\mouse.h"
#include <vector>

Mouse::Mouse(const std::vector<GameObject*>& objects) :
    gameObjects(objects)
{

}

Mouse::~Mouse()
{
}

void Mouse::mouse_button_callback(int button, int action, int x, int y)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        m_leftMouseButton.isPressed = (action == GLFW_PRESS);
        m_leftMouseButton.x = x;
        m_leftMouseButton.y = y;
    }
}
