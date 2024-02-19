#include "Viewport\window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Viewport/scene.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


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
    //glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

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
        ProcessInput();
        glClear(GL_COLOR_BUFFER_BIT);
        _scene->Update(this->width, this->height);
        ImGuiLoop();

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
