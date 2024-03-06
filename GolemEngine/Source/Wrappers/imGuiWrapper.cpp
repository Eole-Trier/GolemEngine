#include "Wrappers/imGuiWrapper.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

ImGuiWrapper& ImGuiWrapper::GetInstance()
{
    static ImGuiWrapper imGuiWrapper;
    return imGuiWrapper;
}

ImGuiWrapper::ImGuiWrapper() {}

ImGuiWrapper::~ImGuiWrapper() {}

void ImGuiWrapper::InitImGui(GLFWwindow* _window)
{
    // Setup Imgui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // Setup style
    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

void ImGuiWrapper::NewFrameImGui()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiWrapper::EditorStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowRounding = 4;
    style.FrameRounding = 4;
    style.GrabRounding = 3;
    style.ScrollbarSize = 7;
    style.ScrollbarRounding = 0;
}

void ImGuiWrapper::LoopImGui()
{
}

