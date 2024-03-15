#include "..\..\Include\Inputs\Mouse.h"

Mouse::Mouse()
{
}

Mouse::~Mouse()
{
}

void Mouse::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        int winWidth, winHeight;
        glfwGetWindowSize(window, &winWidth, &winHeight);

        double x = (2.0 * xpos) / winWidth - 1.0;
        double y = 1.0 - (2.0 * ypos) / winHeight;

        unsigned char pixel[3];
        glReadPixels(xpos, winHeight - ypos, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
    }
}

