#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Viewport\window.h"


#include <iostream>

Window::Window() {}

Window::~Window() {}

Window::Window(std::string _name, unsigned int _width, unsigned int _height) 
    : m_name(_name), width(_width), height(_height) {}

void Window::Init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(width, height, m_name.c_str(), NULL, NULL);
    if (m_window == NULL) 
    {
        std::cout << "Failed to create GLFW window : " << m_name << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(m_window);
    //glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    glEnable(GL_DEPTH_TEST);
}

void Window::Render()
{
    while (!glfwWindowShouldClose(m_window))
    {
        ProcessInput();

        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

void Window::Close()
{
    glfwTerminate();
}

void Window::ProcessInput()
{
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_window, true);
    }
}