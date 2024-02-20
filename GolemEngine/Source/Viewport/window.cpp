#include "Viewport\window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Viewport/scene.h"
#include "Viewport/camera.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

float Window::m_lastX = 400;
float Window::m_lastY = 300;
float Window::m_yaw = 0;
float Window::m_pitch = 0;
bool Window::m_firstMouse = true;

Window::Window() {}

Window::~Window() {}

Window::Window(const char* _name, unsigned int _width, unsigned int _height) 
    : m_name(_name), width(_width), height(_height) {}

GLFWwindow* Window::GetWindow()
{
    return m_window;
}

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
    glfwSetFramebufferSizeCallback(m_window, ResizeCallback);
    glfwSetCursorPosCallback(m_window, MouseCallback);
    glfwSetScrollCallback(m_window, ScrollCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    glEnable(GL_DEPTH_TEST);
    ImGuiInit();
}

void Window::Render(Scene* _scene)
{
    _scene->Init();
    while (!glfwWindowShouldClose(m_window))
    {
        UpdateDeltaTime();
        ProcessInput(_scene->Camera);
        glClear(GL_COLOR_BUFFER_BIT);
        _scene->Update(this->width, this->height, m_window, DeltaTime);
        ImGuiLoop();

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

void Window::Close()
{
    glfwTerminate();
}

void Window::UpdateDeltaTime()
{
    float currentFrame = static_cast<float>(glfwGetTime());
    DeltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;
}


void Window::ProcessInput(Camera& _camera)
{
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_window, true);
    }
    _camera.ProcessInput(m_window, DeltaTime);
}

void Window::ImGuiInit()
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

void Window::ImGuiLoop()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Hello, Golem!");
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Window::ImGuiClean()
{
}

void Window::ResizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Window::MouseCallback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (m_firstMouse)
    {
        m_lastX = xpos;
        m_lastY = ypos;
        m_firstMouse = false;
    }

    float xoffset = xpos - m_lastX;
    float yoffset = m_lastY - ypos;

    m_lastX = xpos;
    m_lastY = ypos;

    Camera* const cam = Camera::Instance;
    cam->ProcessMouseMovement(xoffset, yoffset);
}

void Window::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    Camera* const cam = Camera::Instance;
    cam->ProcessMouseScroll(yoffset);

}