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

}
