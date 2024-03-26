#include "..\..\Include\Inputs\mouse.h"
#include <vector>

Mouse::Mouse(const std::vector<GameObject*>& objects) :
    gameObjects(objects)
{

}

Mouse::~Mouse()
{
}

void Mouse::mouse_button_callback(GLFWwindow* window, int button, int action)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        int winWidth, winHeight;
        glfwGetWindowSize(window, &winWidth, &winHeight);

        unsigned char pixel[3];
        glReadPixels(xpos, winHeight - ypos, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

        selectObjectByColor(pixel[0], pixel[1], pixel[2]);
    }
}
